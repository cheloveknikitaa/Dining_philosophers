/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:38:15 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/13 21:37:38 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

long long	ft_atoi(const char *str)
{
	int			i;
	long long	j;
	long long	m;

	i = 0;
	j = 0;
	m = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = (j * 10) + (str[i] - '0');
		i++;
	}
	return (j * m);
}

long long	get_time(t_info *info)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	info->time = (time.tv_sec % 1000) * 1000 + time.tv_usec / 1000;
	return (info->time);
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
		write(2, str, ft_strlen(str));
	return (-1);
}

void	destroy_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
