/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:55 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/26 12:48:09 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_join_threads(t_set *set, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < set->created_threads)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
		{
			ft_putstr_fd("Failed pthread_join philos\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_destroy_forks(t_set *set)
{
	int	i;

	i = set->nbr_of_philo -1;
	if (set == NULL || set->forks == NULL)
		return ;
	while (i >= 0)
	{
		if (set->forks[i] != NULL)
		{
			pthread_mutex_destroy(set->forks[i]);
			free(set->forks[i]);
			set->forks[i] = NULL;
		}
		else
			ft_putstr_fd("Fork=NULL\n", 2);
		--i;
	}
	free(set->forks);
	set->forks = NULL;
}

void	ft_destroy_philos(t_set *set)
{
	int	i;

	i = set->nbr_of_philo - 1;
	if (!set || !set->philos)
		return ;
	while (i >= 0)
	{
		if (set->philos[i])
		{
			pthread_mutex_destroy(&set->philos[i]->last_meal_mutex);
			free(set->philos[i]);
			set->philos[i] = NULL;
		}
		--i;
	}
	free(set->philos);
	set->philos = NULL;
}

void	ft_destroy_mutexes(t_set *set)
{
	pthread_mutex_destroy(&set->m.current_mutex);
	pthread_mutex_destroy(&set->m.print_mutex);
	pthread_mutex_destroy(&set->m.flag_mutex);
	pthread_mutex_destroy(&set->m.meals_mutex);
}

void	ft_destroy(t_set *set)
{
	if (!set)
		return ;
	if (set->forks)
		ft_destroy_forks(set);
	ft_destroy_mutexes(set);
}
