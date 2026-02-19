/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tprw_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:06 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/26 12:48:40 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(int id, char *str, t_set *set)
{
	int	print_time;

	print_time = ft_safe_current_time_start(set);
	pthread_mutex_lock(&set->m.print_mutex);
	if (ft_safe_read_flag(set) && ft_strcmp(str, DIED) != 0)
	{
		pthread_mutex_unlock(&set->m.print_mutex);
		return ;
	}
	printf("%d %d %s\n", print_time, id, str);
	pthread_mutex_unlock(&set->m.print_mutex);
}

int	ft_safe_read_flag(t_set *set)
{
	int	flag;

	pthread_mutex_lock(&set->m.flag_mutex);
	flag = set->flag;
	pthread_mutex_unlock(&set->m.flag_mutex);
	return (flag);
}

int	ft_safe_read_last_meal(t_philo *philo)
{
	int	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal);
}

void	ft_meals_count(t_set *set, t_philo *philo)
{
	pthread_mutex_lock(&set->m.meals_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&set->m.meals_mutex);
}

int	ft_safe_read_meals_count(t_philo *philo)
{
	int	meals;

	if (!philo->set)
	{
		ft_putstr_fd("philo or philo->set is NULL\n", 2);
		return (-1);
	}
	pthread_mutex_lock(&philo->set->m.meals_mutex);
	meals = philo->meals_counter;
	pthread_mutex_unlock(&philo->set->m.meals_mutex);
	return (meals);
}
