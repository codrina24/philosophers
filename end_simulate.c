/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:24:59 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/28 16:28:26 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_flag(t_set *set, int reason)
{
	(void)reason;
	pthread_mutex_lock(&set->m.flag_mutex);
	if (set->flag == 0)
		set->flag = 1;
	pthread_mutex_unlock(&set->m.flag_mutex);
}

int	ft_check_death(t_philo *philo)
{
	int	since_last_meal;
	int	since_start;
	int	last_meal;

	if (philo == NULL || philo->set == NULL)
		return (1);
	last_meal = ft_safe_read_last_meal(philo);
	since_last_meal = ft_get_times() - last_meal;
	since_start = ft_safe_current_time_start(philo->set);
	if (philo->set->max_meals == -1 || philo->set->max_meals > 0)
	{
		if (last_meal == 0 && since_start > philo->set->time_to_saygoodbye)
		{
			ft_flag(philo->set, DEATH);
			return (ft_print(philo->id, DIED, philo->set), 1);
		}
		if (since_last_meal >= philo->set->time_to_saygoodbye)
		{
			ft_flag(philo->set, DEATH);
			return (ft_print(philo->id, DIED, philo->set), 1);
		}
	}
	return (0);
}

void	*ft_error_handle_lock(t_set *set)
{
	if (pthread_mutex_lock(&set->m.meals_mutex) != 0)
	{
		perror("Error locking meals mutex\n");
		return (NULL);
	}
	return (NULL);
}

void	*ft_error_handle_unlock(t_set *set)
{
	if (pthread_mutex_unlock(&set->m.meals_mutex) != 0)
	{
		perror("Error unlocking meals mutex\n");
		return (NULL);
	}
	return (NULL);
}

void	*ft_simultan_monitor(void *arg)
{
	int		i;
	int		all_ate_flag;
	t_set	*set;

	set = (t_set *)arg;
	while (1)
	{
		all_ate_flag = 1;
		i = 0;
		while (i < set->nbr_of_philo)
		{
			if (ft_check_in(set, i) == 1)
				return (NULL);
			ft_error_handle_lock(set);
			if (set->max_meals > 0
				&& set->philos[i]->meals_counter < set->max_meals)
				all_ate_flag = 0;
			ft_error_handle_unlock(set);
			i++;
		}
		if (set->max_meals > 0 && all_ate_flag == 1)
			return (ft_flag(set, MAX_ATE), ft_putstr_fd("MMx\n", 2), NULL);
		usleep(100);
	}
	return (NULL);
}
