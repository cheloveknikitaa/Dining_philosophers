/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:10:54 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/22 15:02:40 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long long time, t_info *info)
{
	long long	time_to_wake;

	time_to_wake = info->time + time;
	while (info->time < time_to_wake)
		usleep(10);
}

void	philo_born(t_info *info, t_philo *philo, int i)
{
	philo[i].info = info;
	philo[i].start = info->time;
	philo[i].deadline = info->time_to_die + info->time;
	philo[i].id = i + 1;
	if (pthread_create(&philo[i].thread, \
		NULL, life_of_philo, (void *)&philo[i]) != 0)
		info->amount_of_cicles = -1;
}

void	joiner(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < info->keep_amount_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	free(philo);
	destroy_forks(forks, info->keep_amount_of_philo);
	free(forks);
	pthread_mutex_destroy(&info->message);
}
