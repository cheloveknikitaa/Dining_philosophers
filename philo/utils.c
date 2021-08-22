/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:10:54 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/22 22:06:24 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long long time, t_info *info)
{
	long long	time_to_wake;

	if (info->dead < 0 || info->all_eating == 0)
		return ;
	time_to_wake = info->time + time;
	while (info->time < time_to_wake)
		usleep(250);
}

void	philo_born(t_info *info, t_philo *philo, int i)
{
	philo[i].info = info;
	philo[i].start = info->time;
	philo[i].amount_of_eating = info->amount_of_cicles;
	philo[i].id = i + 1;
	philo[i].deadline = info->time_to_die + info->time;
	if (pthread_create(&philo[i].thread, \
		NULL, life_of_philo, (void *)&philo[i]) != 0)
		info->dead = -1;
	pthread_detach(philo[i].thread);
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
	info->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (info->time);
}

int	this_is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
