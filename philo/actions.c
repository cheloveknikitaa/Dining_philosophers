/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:11:02 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/22 18:13:10 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->all_philo_eating == 0 || \
		philo->info->amount_of_philo == -1)
	{
		if (ft_strlen(str) == 11)
		{
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
		}
		pthread_mutex_unlock(&philo->info->message);
		return (-1);
	}
	else if (str != NULL)
	{
		printf("%lld %d %s", ((philo->info->time - philo->start)), \
			philo->id, str);
		pthread_mutex_unlock(&philo->info->message);
	}
	else
		pthread_mutex_unlock(&philo->info->message);
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
		if (forks_taker(philo, 0) == -1)
			return (NULL);
		philo->deadline = philo->info->time + philo->info->time_to_die;
		if (print("is eating\n", philo) == -1)
			return (NULL);
		my_usleep(philo->info->time_to_eat, philo->info);
		if (forks_taker(philo, 1) == -1)
			return (NULL);
		if (--n == 0)
			philo->info->all_philo_eating--;
		if (print("is sleeping\n", philo) == -1)
			return (NULL);
		my_usleep(philo->info->time_to_sleep, philo->info);
		if (print("is thinking\n", philo) == -1)
			return (NULL);
	}
	philo->info->amount_of_cicles = -1;
	return (NULL);
}

int	death(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	while (1)
	{
		i = 0;
		usleep(250);
		while (i < info->amount_of_philo && info->all_philo_eating != 0)
		{
			if (philo[i].deadline < get_time(info))
			{
				info->amount_of_philo = -1;
				printf("%lld %d %s", \
				((info->time - philo[i].start)) \
				, philo[i].id, " died.\n");
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
	return (free_all(info, philo, forks));
}

int	init_philo(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	info->time = get_time(info);
	while (i < info->amount_of_philo && info->amount_of_cicles != -1)
	{
		if ((i + 1) % 2 == 0)
			philo_born(info, philo, i);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < info->amount_of_philo && info->amount_of_cicles != -1)
	{
		if ((i + 1) % 2 != 0)
			philo_born(info, philo, i);
		i++;
	}
	if (info->amount_of_cicles == -1)
	{
		pthread_mutex_destroy(&info->message);
		destroy_forks(forks, info->keep_amount_of_philo);
		return (-1);
	}
	return (0);
}
