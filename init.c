/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:19 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/28 16:43:44 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_set *set, t_mutex *m)
{
	if (pthread_mutex_init(&m->current_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&m->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&m->current_mutex);
		return (-1);
	}
	if (pthread_mutex_init(&m->flag_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&m->print_mutex);
		pthread_mutex_destroy(&m->current_mutex);
		return (-1);
	}
	if (pthread_mutex_init(&m->meals_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&set->m.current_mutex);
		pthread_mutex_destroy(&set->m.print_mutex);
		pthread_mutex_destroy(&set->m.flag_mutex);
		return (-1);
	}
	return (0);
}

int	ft_max_meal_set(int argc, char **argv, t_set *set)
{
	bool	error;

	if (argc == 6)
	{
		set->max_meals = ft_atol(argv[5], &error);
		if (error || set->max_meals == 0)
			return (ft_putstr_fd("Limit ko or at least one meal\n", 2), 1);
	}
	else if (argc == 5)
		set->max_meals = -1;
	return (0);
}

int	check_limit_arg(t_set *set, char **argv)
{
	bool	error;

	set->nbr_of_philo = ft_atol(argv[1], &error);
	if (error || set->nbr_of_philo == 0)
		return (ft_putstr_fd("Error limit or philo number\n", 2), 1);
	set->time_to_saygoodbye = ft_atol(argv[2], &error);
	if (error || set->time_to_saygoodbye == 0)
		return (ft_putstr_fd("Time to die ko\n", 2), 1);
	set->time_to_eat = ft_atol(argv[3], &error);
	if (error || set->time_to_eat == 0)
		return (ft_putstr_fd("Time to eat ko\n", 2), 1);
	set->time_to_sleep = ft_atol(argv[4], &error);
	if (error || set->time_to_sleep == 0)
		return (ft_putstr_fd("Time to sleep ko\n", 2), 1);
	return (0);
}

int	ft_set_init(t_set *set, int argc, char **argv)
{
	if (check_limit_arg(set, argv) == 1)
		return (1);
	if (ft_max_meal_set(argc, argv, set) == 1)
		return (1);
	if (ft_init_mutex(set, &set->m) == -1)
		return (ft_putstr_fd("Mutex init failed\n", 2), 1);
	set->start_time = ft_safe_start(set);
	set->flag = 0;
	set->created_threads = 0;
	if (ft_mem_forks(set) == -1)
		return (1);
	if (ft_mem_philo(set) == -1)
	{
		ft_destroy_forks(set);
		return (1);
	}
	return (0);
}

int	ft_philo_init(t_philo *philo, int i, t_set *set, pthread_mutex_t **forks)
{
	philo->id = i + 1;
	philo->meals_counter = 0;
	philo->last_meal_time = ft_get_times();
	philo->left_fork = forks[i];
	philo->right_fork = forks[(i + 1) % set->nbr_of_philo];
	philo->set = set;
	philo->left = 0;
	philo->right = 0;
	return (0);
}
