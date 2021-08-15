/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:00:36 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/15 18:36:12 by caugusta         ###   ########.fr       */
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
	long long		time_to_sleap;
	long long		time;
	int				amount_of_philo;
	int				amount_of_cicles;
	int				amount_of_forks;
	int				all_philo_eating;
}				t_info;

typedef struct s_philo
{
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t			thread;
	t_info				*info;
	long long			start;
	long long			deadline;
	int					id;
}				t_philo;

long long	ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
int			print(char *str, t_philo *philo);
void		*life_of_philo(void	*ph);
int			parser(int argc, char **argv, t_info *info);
int			exit_error(char *str, pthread_mutex_t *forks, t_philo *philo);
void		gets_forks(t_info *info, pthread_mutex_t *forks, t_philo *philo);
int			init_philo(t_info *info, t_philo *philo, pthread_mutex_t *forks);
int			inits_forks(pthread_mutex_t *forks, int i);
long long	get_time(t_info *info);
void		death(t_info *info, t_philo *philo, pthread_mutex_t *forks);
void		destroy_forks(pthread_mutex_t *forks, int n);
int			this_is_num(char **argv);
void		forks_take_down(char *str, t_philo *philo, pthread_mutex_t *fork, int i);
void		my_usleep(long long sec);


#endif