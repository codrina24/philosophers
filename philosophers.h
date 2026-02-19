/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:09:33 by coholbur          #+#    #+#             */
/*   Updated: 2025/05/26 12:46:42 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

# define THINK "is thinking"
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "\033[31mdied\033[0m"
# define MAX_ATE 0
# define DEATH 1

typedef struct s_philo	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	current_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	meals_mutex;
}						t_mutex;

typedef struct s_set
{
	int					nbr_of_philo;
	int					time_to_saygoodbye;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	long long			start_time;
	int					flag;
	int					created_threads;
	pthread_mutex_t		**forks;
	t_mutex				m;
	t_philo				**philos;
}								t_set;

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	int					meals_counter;
	int					last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		last_meal_mutex;
	t_set				*set;
}						t_philo;

int		ft_strcmp(char *s1, char *s2);
long	ft_atol(const char *nptr, bool *error);
int		ft_isdigit(int c);
int		check_limit_arg(t_set *set, char **argv);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
int		ft_check_argc(int argc);
int		ft_check_argv(char **argv);
int		ft_check_arg(int argc, char **argv);
int		ft_mutex_forks_init(t_set *set);
int		ft_max_meal_set(int argc, char **argv, t_set *set);
int		ft_init_mutex(t_set *set, t_mutex *m);
int		ft_safe_start(t_set *set);
int		ft_set_init(t_set *set, int argc, char **argv);
int		ft_philo_init(t_philo *philo, int i,
			t_set *set, pthread_mutex_t **forks);
int		ft_safe_lm(t_philo *philo);
int		ft_get_time(void);
int		ft_get_start_time(int reset);
int		ft_get_times(void);
void	ft_print(int id, char *str, t_set *set);
int		ft_safe_current_time_start(t_set *set);
int		ft_safe_current_time_lm(t_philo *philo);
void	ft_safe_set_last_meal(t_philo *philo, int time);
int		ft_safe_read_last_meal(t_philo *philo);
void	ft_flag(t_set *set, int reason);
int		ft_safe_read_flag(t_set *set);
void	ft_meals_count(t_set *set, t_philo *philo);
int		ft_safe_read_meals_count(t_philo *philo);
int		ft_check_in(t_set *set, int i);
int		ft_mem_forks(t_set *set);
int		ft_mem_philo(t_set *set);
int		ft_create_threads(t_set *set);
int		ft_join_threads(t_set *set, t_philo **philos);
void	ft_destroy_forks(t_set *set);
void	ft_destroy_philos(t_set *set);
void	ft_destroy_mutexes(t_set *set);
void	ft_destroy(t_set *set);
void	ft_unlock(t_philo *philo);
void	ft_philosophers_init(t_philo *philo,
			pthread_mutex_t *forks, int num_philos);
int		ft_check_min(t_set *set, t_philo *philo);
int		ft_check_death(t_philo *philo);
void	*ft_simulate_life(void *arg);
void	*ft_error_handle_lock(t_set *set);
void	*ft_error_handle_unlock(t_set *set);
void	*ft_simultan_monitor(void *arg);

#endif