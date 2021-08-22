/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:11:02 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/22 22:13:10 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->dead > 0 && philo->info->all_eating > 0)
		printf("%lld %d %s\n", (philo->info->time - philo->start), \
				philo->id, str);
	pthread_mutex_unlock(&philo->info->message);
}

void	*life_of_philo(void	*ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (philo->info->dead > 0 && philo->info->all_eating > 0)
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
		if (philo->info->dead > 0 && philo->info->all_eating > 0)
			print("has taken a fork", philo);
		if (philo->info->dead > 0 && philo->info->all_eating > 0)
			print("is eating", philo);
		if (philo->info->dead > 0 && philo->info->all_eating > 0)
			philo->deadline = philo->info->time + philo->info->time_to_die;
		my_usleep(philo->info->time_to_eat, philo->info);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		if (--philo->amount_of_eating == 0)
			philo->info->all_eating--;
		if (philo->info->dead > 0 && philo->info->all_eating > 0)
			print("is sleeping", philo);
		my_usleep(philo->info->time_to_sleep, philo->info);
		if (philo->info->dead > 0 && philo->info->all_eating > 0)
			print("is thinking", philo);
	}
	return (NULL);
}

int	death(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	while (info->dead > 0 && info->all_eating > 0)
	{
		i = 0;
		while (i < info->amount_of_philo)
		{
			if (philo[i].deadline < get_time(info))
			{
				print("died", philo);
				info->dead = -1;
			}
			i++;
		}
	}
	return (free_all(info, philo, forks));
}

int	exit_error(char *str, pthread_mutex_t *forks, t_philo *philo)
{
	if (forks != NULL)
	{
		free(forks);
		forks = NULL;
	}
	if (philo != NULL)
	{
		free(philo);
		philo = NULL;
	}
	if (str != NULL)
		printf("%s", str);
	return (-1);
}

int	free_all(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < info->amount_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	destroy_forks(forks, info->amount_of_philo);
	pthread_mutex_destroy(&info->message);
	free(forks);
	free(philo);
	return (0);
}
