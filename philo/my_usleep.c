/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 19:10:54 by caugusta          #+#    #+#             */
/*   Updated: 2021/08/15 19:50:44 by caugusta         ###   ########.fr       */
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
