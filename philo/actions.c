/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:11:02 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/13 22:22:53 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->amount_of_cicles == -1 || \
		philo->info->amount_of_philo == -1)
	{
		if (ft_strlen(str) == 14)
		{
			pthread_mutex_unlock(philo->left);
			pthread_mutex_unlock(philo->right);
		}
		pthread_mutex_unlock(&philo->info->message);
		return (-1);
	}
	else
	{
		printf("%lld %d %s", ((philo->info->time - philo->start)), \
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
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
		philo->deadline += philo->info->time_to_eat + philo->info->time_to_die;
		if (print("eating start\n", philo) == -1)
			return (NULL);
		usleep(philo->info->time_to_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		if (print("eating end and go to sleep\n", philo) == -1)
			return (NULL);
		if (--n == 0)
			break ;
		usleep(philo->info->time_to_sleap);
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
		while (i < info->amount_of_philo && info->amount_of_cicles != -1)
		{
			if (philo[i].deadline < get_time(info))
			{
				info->amount_of_philo = -1;
				printf("%lld %d %s", \
				((info->time - philo[i].start)) \
				, philo->id, " philo dead.\nEnd of simulation\n");
				break ;
			}
			i++;
		}
		if (info->amount_of_cicles == -1)
		{
			printf("%s", "End of simulation\n");
			break ;
		}
	}
	destroy_forks(forks, info->amount_of_forks);
}
