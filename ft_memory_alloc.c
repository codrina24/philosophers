/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:04 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/23 11:37:52 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_mem_forks(t_set *set)
{
	int				i;
	pthread_mutex_t	**forks;

	forks = malloc(sizeof(pthread_mutex_t *) * set->nbr_of_philo);
	if (!forks)
		return (ft_putstr_fd("P_thread_mutex mem alloc failed\n", 2), -1);
	i = 0;
	set->forks = forks;
	while (i < set->nbr_of_philo)
	{
		set->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!set->forks[i])
		{
			ft_destroy_forks(set);
			return (ft_putstr_fd("Forks mem alloc failed\n", 2), -1);
		}
		memset(set->forks[i], 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(set->forks[i], NULL) != 0)
		{
			ft_destroy_forks(set);
			return (ft_putstr_fd("Forks_mutex init failed\n", 2), -1);
		}
		i++;
	}
	return (0);
}

int	ft_mem_philo(t_set *set)
{
	int			i;
	t_philo		**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * set->nbr_of_philo);
	if (!philos)
		return (ft_putstr_fd("T_philos mem alloc failed\n", 2), -1);
	while (i < set->nbr_of_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			ft_destroy_philos(set);
			return (ft_putstr_fd("Philos mem alloc failed\n", 2), -1);
		}
		memset(philos[i], 0, sizeof(t_philo));
		if (pthread_mutex_init(&philos[i]->last_meal_mutex, NULL) != 0)
		{
			ft_destroy_philos(set);
			return (ft_putstr_fd("Last_meal_mutex init failed\n", 2), -1);
		}
		i++;
	}
	set->philos = philos;
	return (0);
}
