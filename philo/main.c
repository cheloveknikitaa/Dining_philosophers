/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:00:08 by caugusta          #+#    #+#             */
/*   Updated: 2021/09/18 19:45:46 by caugusta         ###   ########.fr       */
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
		return (-1);
	if (info.amount_of_cicles == 0 || info.amount_of_philo == 0)
		return (0);
	forks = malloc(sizeof(pthread_mutex_t) * info.amount_of_philo);
	if (forks == NULL)
		return (exit_error("Error, malloc is not allocated\n", NULL, NULL));
	philo = malloc(sizeof(t_philo) * info.amount_of_philo);
	if (philo == NULL)
		return (exit_error("Error, malloc is not allocated\n", forks, NULL));
	if (inits_forks(&info, forks, philo) == -1)
		return (exit_error("Error, inits mutex error\n", forks, philo));
	if (init_philo(&info, philo, forks) == -1)
		return (exit_error("Error, thread create error\n", forks, philo));
	return (death(&info, philo, forks));
}

int	parser(int argc, char **argv, t_info *info)
{
	if (this_is_num(argv) == -1)
		return (exit_error("Error, invalid arguments\n", NULL, NULL));
	info->amount_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	if (info->time_to_die < 1)
		return (exit_error("Error, invalid arguments\n", NULL, NULL));
	info->time_to_eat = ft_atoi(argv[3]);
	if (info->time_to_eat < 1)
		return (exit_error("Error, invalid arguments\n", NULL, NULL));
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->time_to_sleep < 1)
		return (exit_error("Error, invalid arguments\n", NULL, NULL));
	if (argc == 6)
		info->amount_of_cicles = ft_atoi(argv[5]);
	else
		info->amount_of_cicles = -2;
	info->all_eating = info->amount_of_philo;
	info->dead = 1;
	return (0);
}

int	inits_forks(t_info *info, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->message, NULL) != 0)
		return (-1);
	while (i < info->amount_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&info->message);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < info->amount_of_philo - 1)
	{
		philo[i].left = &forks[i];
		philo[i].right = &forks[i + 1];
		i++;
	}
	philo[i].left = &forks[i];
	philo[i].right = &forks[0];
	return (0);
}

int	init_philo(t_info *info, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	info->time = get_time(info);
	while (i < info->amount_of_philo && info->dead != -1)
	{
		if ((i + 1) % 2 == 0)
			philo_born(info, philo, i);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < info->amount_of_philo && info->dead != -1)
	{
		if ((i + 1) % 2 != 0)
			philo_born(info, philo, i);
		i++;
	}
	if (info->dead == -1)
	{
		pthread_mutex_destroy(&info->message);
		destroy_forks(forks, info->amount_of_philo);
		return (-1);
	}
	return (0);
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
