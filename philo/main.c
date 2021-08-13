/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:00:08 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/13 22:17:36 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_mutex_t	*forks;
	t_philo			*philo;

	if (argc < 5)
		return (exit_error("Error, not enough arguments\n", NULL, NULL));
	if (argc > 6)
		return (exit_error("Error, too much arguments\n", NULL, NULL));
	if (parser(argc, argv, &info) == -1)
		return (exit_error("Error, invalid arguments\n", NULL, NULL));
	if (info.amount_of_cicles == 0 && info.amount_of_philo == 0)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * info.amount_of_philo);
	if (forks == NULL)
		return (exit_error("Error, malloc is not allocated\n", NULL, NULL));
	philo = malloc(sizeof(t_philo) * info.amount_of_philo);
	if (philo == NULL)
		return (exit_error("Error, malloc is not allocated\n", forks, NULL));
	if (inits_forks(forks, info.amount_of_philo) == -1)
		return (exit_error("Error, forks inits mutex error\n", forks, philo));
	if (init_philo(&info, philo, forks) == -1)
		return (exit_error("Error, thread create error\n", forks, philo));
	death(&info, philo, forks);
	pthread_mutex_destroy(&info.message);
	return (0);
}

int	parser(int argc, char **argv, t_info *info)
{
	// eto chisla?
	info->amount_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]) * 1000;
	if (info->time_to_die < 1)
		return (-1);
	info->time_to_eat = ft_atoi(argv[3]) * 1000;
	if (info->time_to_eat < 1)
		return (-1);
	info->time_to_sleap = ft_atoi(argv[4]) * 1000;
	if (info->time_to_sleap < 1)
		return (-1);
	if (argc == 6)
		info->amount_of_cicles = ft_atoi(argv[5]);
	else
		info->amount_of_cicles = -2;
	if (pthread_mutex_init(&info->message, NULL) != 0)
		return (-1); // add msg error
	return (0);
}

void	gets_forks(t_info *info, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 1;
	philo[0].left = &forks[info->amount_of_philo - 1];
	philo[0].right = &forks[0];
	while (i < info->amount_of_philo - 1)
	{
		if (i % 2 != 0)
		{
			philo[i].left = &forks[i];
			philo[i].right = &forks[i - 1];
		}
		else
		{
			philo[i].left = &forks[i - 1];
			philo[i].right = &forks[i];
		}
		i++;
	}
	philo[i].left = &forks[i];
	philo[i].right = &forks[0];
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

int	inits_forks(pthread_mutex_t *forks, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (pthread_mutex_init(&forks[j], NULL) != 0)
			return (-1);
		j++;
	}
	return (0);
}
