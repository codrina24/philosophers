/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:06:13 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/23 13:08:08 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_get_time(void)
{
	struct timeval	tv;
	long			tstamp;

	memset(&tv, 0, sizeof(struct timeval));
	tstamp = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	tstamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (tstamp);
}

int	ft_safe_start(t_set *set)
{
	int	time;

	pthread_mutex_lock(&set->m.current_mutex);
	time = ft_get_time();
	pthread_mutex_unlock(&set->m.current_mutex);
	return (time);
}

int	ft_get_start_time(int reset)
{
	static int		start;

	if (reset == 1)
	{
		start = 0;
		return (0);
	}
	if (start != 0)
		return (start);
	start = ft_get_time();
	return (start);
}

int	ft_get_times(void)
{
	int	time;
	int	start;

	start = ft_get_start_time(0);
	time = ft_get_time();
	time = time - start;
	return (time);
}

int	ft_safe_current_time_start(t_set *set)
{
	int	time;

	if (!set)
		return (-1);
	pthread_mutex_lock(&set->m.current_mutex);
	time = ft_get_time() - set->start_time;
	pthread_mutex_unlock(&set->m.current_mutex);
	return (time);
}
