/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:44 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/09 14:27:03 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>//
# include <stdlib.h> //
# include <stdio.h> //

/*default parameters*/

# ifndef MIN_PHILO_COUNT
#  define MIN_PHILO_COUNT 1
# endif

# ifndef MAX_PHILO_COUNT
#  define MAX_PHILO_COUNT 200
# endif

# ifndef MIN_TIME_TO_DIE
#  define MIN_TIME_TO_DIE 60
# endif

# ifndef MIN_TIME_TO_EAT
#  define MIN_TIME_TO_EAT 60
# endif

# ifndef MIN_TIME_TO_SLEEP
#  define MIN_TIME_TO_SLEEP 60
# endif

# ifndef DEFAULT_TIMES_EATEN_TO_END
#  define DEFAULT_TIMES_EATEN_TO_END -1
# endif

typedef struct s_parameters
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_eaten;
}	t_params;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct timeval	t_time;

typedef struct s_philosopher
{
	t_params		params;

	int				id;
	bool			*can_eat;
	bool			*dead;
	// t_state			state;
	t_time			time_last_eaten;
	// int				times_eaten;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	// pthread_mutex_t	*info_lock;
}	t_philo;

typedef struct s_table
{
	// int				*times_eaten;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	// pthread_mutex_t	*info_lock;
	bool			*can_eat;
	bool			*dead;
	pthread_t		*threads;
}	t_table;

// typedef struct s_philosopher
// {
// 	unsigned int	id;
// 	pthread_t		*thread;
	// pthread_mutex_t	*r_fork;
	// pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*state;
// 	unsigned int	times_eaten;
// 	unsigned int	time_last_eaten;

// 	t_params		params;
// }	t_philo;

void	*routine(void *param);

/*params.c*/

int		check_arg_count(int argc);
int		ft_atoi(const char *str);
int		check_params(t_params *p);
int		set_params(t_params *params, int argc, char **argv);

// /*routine.c*/

// void	*routine(void *param);

// /*table.c*/

// void	init_philos(t_params params, t_table *table);
// int		init_table(t_table *table, t_params params);
int		set_table(t_table *table, t_params params);

// /*utils.c*/

// void	*ph_calloc(size_t count, size_t size);

#endif