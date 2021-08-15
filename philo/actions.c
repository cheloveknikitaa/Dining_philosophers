/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:11:02 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/15 20:06:22 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->all_philo_eating == 0 || \
		philo->info->amount_of_philo == -1)
	{
		if (ft_strlen(str) == 14)
		{
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
		}
		pthread_mutex_unlock(&philo->info->message);
		return (-1);
	}
	else
	{
		printf("%lld %d %s", ((philo->info->time - philo->start) / 1000) + 1, \
			philo->id, str);
		pthread_mutex_unlock(&philo->info->message);
	}
	return (0);
}

void	*life_of_philo(void	*ph)
{
	t_philo	*philo;
	int		n;

	philo = (t_philo *)ph;
	n = philo->info->amount_of_cicles;
	while (n != 0)
	{
		forks_take("take first fork\n", philo, 1);
		forks_take("take second fork\n", philo, 2);
		philo->deadline += philo->info->time_to_eat + philo->info->time_to_die;
		if (print("eating start\n", philo) == -1)
			return (NULL);
		my_usleep(philo->info->time_to_eat, philo->info);
		forks_down("down second fork\n", philo, 1);
		forks_down("down first fork\n", philo, 2);
		if (print("eating end and go to sleep\n", philo) == -1)
			return (NULL);
		if (--n == 0)
			philo->info->all_philo_eating--;
		my_usleep(philo->info->time_to_sleap, philo->info);
		if (print("thinking\n", philo) == -1)
			return (NULL);
	}
	philo->info->amount_of_cicles = -1;
	return (NULL);
}

void	death(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	info->amount_of_forks = info->amount_of_philo;
	while (1)
	{
		i = 0;
		while (i < info->amount_of_philo && info->all_philo_eating != 0)
		{
			if (philo[i].deadline < get_time(info))
			{
				info->amount_of_philo = -1;
				printf("%lld %d %s", \
				((info->time - philo[i].start) / 1000) + 1 \
				, philo[i].id, " philo dead.\n");
				break ;
			}
			i++;
		}
		if (info->all_philo_eating == 0 || info->amount_of_philo == -1)
		{
			printf("%s", "End of simulation\n");
			break ;
		}
	}
	destroy_forks(forks, info->amount_of_forks);
}

int	init_philo(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	gets_forks(info, forks, philo);
	info->time = get_time(info);
	while (i < info->amount_of_philo && info->amount_of_cicles != -1)
	{
		philo[i].info = info;
		philo[i].start = info->time;
		philo[i].deadline = info->time_to_die + info->time;
		philo[i].id = i + 1;
		if (info->amount_of_cicles != -1 && pthread_create(&philo[i].thread, \
			NULL, life_of_philo, (void *)&philo[i]) != 0)
			info->amount_of_cicles = -1;
		if (info->amount_of_cicles != -1 && \
			pthread_detach(philo[i].thread) != 0)
			info->amount_of_cicles = -1;
		i++;
	}
	if (info->amount_of_cicles == -1)
	{
		destroy_forks(forks, info->amount_of_philo);
		return (-1);
	}
	return (0);
}

void	forks_take(char *str, t_philo *ph, int try)
{
	if (try == 1)
	{
		if (ph->id % 2 == 0)
			pthread_mutex_lock(ph->left);
		else
			pthread_mutex_lock(ph->right);
	}
	else
	{
		if (ph->id % 2 == 0)
			pthread_mutex_lock(ph->right);
		else
			pthread_mutex_lock(ph->left);
	}
	if (print(str, ph) == -1)
		return ;
}

void	forks_down(char *str, t_philo *ph, int try)
{
	if (try == 1)
	{
		if (ph->id % 2 == 0)
			pthread_mutex_unlock(ph->right);
		else
			pthread_mutex_unlock(ph->left);
	}
	else
	{
		if (ph->id % 2 == 0)
			pthread_mutex_unlock(ph->left);
		else
			pthread_mutex_unlock(ph->right);
	}
	if (print(str, ph) == -1)
		return ;
}
