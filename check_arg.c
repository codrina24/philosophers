/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:24:10 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/22 15:42:13 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Error nbr of arg\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
				j++;
			if (!ft_isdigit(argv[i][j]))
			{
				ft_putstr_fd("Error not a digit\n", 2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_arg(int argc, char **argv)
{
	if (ft_check_argc(argc) != 0)
	{
		return (1);
	}
	if (ft_check_argv(argv) != 0)
	{
		return (1);
	}
	return (0);
}
