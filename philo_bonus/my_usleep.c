/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:10:54 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/16 11:27:40 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long long time, t_info *info)
{
	long long	time_to_wake;

	time_to_wake = info->time + time;
	while (info->time / 1000 < time_to_wake / 1000)
		usleep(10);
}

void	philo_born(t_info *info, t_philo *philo, int i)
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
}
