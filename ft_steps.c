/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:38:55 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/28 16:44:36 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_create_threads(t_set *set)
{
	int		i;
	t_philo	**philos;

	philos = set->philos;
	i = 0;
	while (i < set->nbr_of_philo)
	{
		if (ft_philo_init(philos[i], i, set, set->forks) != 0)
		{
			ft_destroy(set);
			set->created_threads = i;
			return (ft_putstr_fd("Philo_init failed\n", 2), 1);
		}
		if (pthread_create(&philos[i]->thread, NULL,
				ft_simulate_life, philos[i]) != 0)
		{
			set->created_threads = i;
			while (--i >= 0)
				pthread_join(philos[i]->thread, NULL);
			return (1);
		}
		i++;
	}
	set->created_threads = i;
	return (0);
}

int	ft_check_min(t_set *set, t_philo *philo)
{
	if (set->nbr_of_philo == 1)
	{
		ft_print(philo->id, TAKE_FORK, philo->set);
		usleep((set->time_to_saygoodbye + 1) * 1000);
		ft_flag(set, DEATH);
		return (1);
	}
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	if (ft_safe_read_flag(philo->set))
		return ;
	ft_print(philo->id, SLEEP, philo->set);
	usleep(philo->set->time_to_sleep * 1000);
	if (ft_safe_read_flag(philo->set))
		return ;
}

void	ft_eat(t_philo *philo)
{
	if (ft_safe_read_flag(philo->set))
		return ;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = ft_get_times();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_meals_count(philo->set, philo);
	ft_print(philo->id, EAT, philo->set);
	usleep(philo->set->time_to_eat * 1000);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

int	ft_check_in(t_set *set, int i)
{
	if (ft_check_death(set->philos[i]) == 1 || ft_safe_read_flag(set) == 1)
		return (1);
	return (0);
}
