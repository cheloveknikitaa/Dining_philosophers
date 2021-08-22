/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:10:54 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/22 18:09:49 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long long time, t_info *info)
{
	long long	time_to_wake;

	if (info->all_philo_eating == 0 || info->amount_of_philo == -1)
		return ;
	time_to_wake = info->time + time;
	while (info->time < time_to_wake)
		usleep(250);
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
	pthread_detach(philo[i].thread);
}

int	free_all(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	free(philo);
	destroy_forks(forks, info->keep_amount_of_philo);
	free(forks);
	pthread_mutex_destroy(&info->message);
	return (0);
}

int	forks_taker(t_philo *philo, int i)
{
	if (i == 0)
	{
		if (forks_take_down(NULL, philo, philo->left, 0) == -1)
			return (-1);
		if (forks_take_down("has taken a fork\n", philo, philo->right, 0) == -1)
			return (-1);
	}
	else
	{
		forks_take_down(NULL, philo, philo->right, 1);
		if (forks_take_down(NULL, philo, philo->left, 1) == -1)
			return (-1);
	}
	return (0);
}

int	forks_take_down(char *str, t_philo *philo, pthread_mutex_t *fork, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(fork);
		if (print(str, philo) == -1)
		{
			pthread_mutex_unlock(fork);
			return (-1);
		}
	}
	else
	{
		pthread_mutex_unlock(fork);
		if (print(str, philo) == -1)
			return (-1);
	}
	return (0);
}
