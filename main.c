/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:25:34 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/26 12:46:17 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	ft_protected_create(t_set *set)
{
	if (ft_create_threads(set) != 0)
	{
		ft_putstr_fd("Error creating threads\n", 2);
		ft_destroy(set);
		return ;
	}
}

void	ft_protected_monitor_thread(t_set *set)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, ft_simultan_monitor, set) != 0)
	{
		ft_putstr_fd("Error creating monitor threads\n", 2);
		ft_destroy(set);
		return ;
	}
	pthread_join(monitor_thread, NULL);
}

void	ft_protected_join_threads(t_set *set, t_philo **philos)
{
	if (ft_join_threads(set, philos) != 0)
	{
		ft_destroy(set);
		return ;
	}
	ft_destroy_philos(set);
}

int	main(int argc, char **argv)
{
	t_set	set;
	t_philo	**philos;

	if (ft_check_arg(argc, argv) != 0)
	{
		return (1);
	}
	if (ft_set_init(&set, argc, argv) != 0)
	{
		return (1);
	}
	set.start_time = ft_safe_start(&set);
	philos = set.philos;
	ft_protected_create(&set);
	ft_protected_monitor_thread(&set);
	ft_protected_join_threads(&set, philos);
	ft_destroy_philos(&set);
	ft_destroy_forks(&set);
	ft_destroy_mutexes(&set);
	return (0);
}
