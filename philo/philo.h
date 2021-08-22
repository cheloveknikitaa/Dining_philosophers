/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:00:36 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/22 22:11:46 by caugusta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	pthread_mutex_t	message;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time;
	int				amount_of_philo;
	int				amount_of_cicles;
	int				dead;
	int				all_eating;
}				t_info;

typedef struct s_philo
{
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t			thread;
	t_info				*info;
	long long			start;
	long long			deadline;
	int					amount_of_eating;
	int					id;
}				t_philo;

void		print(char *str, t_philo *philo);
void		*life_of_philo(void	*ph);
int			death(t_info *info, t_philo *philo, pthread_mutex_t *forks);
int			exit_error(char *str, pthread_mutex_t *forks, t_philo *philo);
int			free_all(t_info *info, t_philo *philo, pthread_mutex_t *forks);
int			main(int argc, char **argv);
int			parser(int argc, char **argv, t_info *info);
int			inits_forks(t_info *info, pthread_mutex_t *forks, t_philo *philo);
int			init_philo(t_info *info, t_philo *philo, pthread_mutex_t *forks);
void		destroy_forks(pthread_mutex_t *forks, int n);
void		my_usleep(long long time, t_info *info);
void		philo_born(t_info *info, t_philo *philo, int i);
long long	ft_atoi(const char *str);
long long	get_time(t_info *info);
int			this_is_num(char **argv);

#endif