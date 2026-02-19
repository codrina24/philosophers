/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:46 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/26 12:47:09 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_take_left_and_right(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_safe_read_flag(philo->set))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	ft_print(philo->id, TAKE_FORK, philo->set);
	pthread_mutex_lock(philo->right_fork);
	if (ft_safe_read_flag(philo->set))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	ft_print(philo->id, TAKE_FORK, philo->set);
	return (1);
}

int	ft_take_right_and_left(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (ft_safe_read_flag(philo->set))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	ft_print(philo->id, TAKE_FORK, philo->set);
	pthread_mutex_lock(philo->left_fork);
	if (ft_safe_read_flag(philo->set))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	ft_print(philo->id, TAKE_FORK, philo->set);
	return (1);
}

void	ft_take_fork(t_philo *philo)
{
	if (ft_safe_read_flag(philo->set))
		return ;
	if (philo->id % 2 != 0)
		ft_take_left_and_right(philo);
	else
		ft_take_right_and_left(philo);
}

void	*ft_simulate_life(void *arg)
{
	t_philo	*philo;
	int		max;

	philo = (t_philo *)arg;
	max = philo->set->max_meals;
	if (!philo || !philo->set)
		return (ft_putstr_fd("ERROR: NULL philo or set\n", 2), NULL);
	if (ft_check_min(philo->set, philo) == 1)
		return (NULL);
	while (ft_get_time() < philo->set->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(1500);
	while ((ft_safe_read_flag(philo->set) == 0)
		&& (max == -1 || philo->meals_counter < max))
	{	
		ft_take_fork(philo);
		ft_eat(philo);
		if (ft_safe_read_flag(philo->set))
			break ;
		ft_sleep(philo);
		ft_print(philo->id, THINK, philo->set);
		usleep(500);
	}
	return (NULL);
}
