/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:44 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/06 11:14:50 by ecastong         ###   ########.fr       */
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
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_eaten;
}	t_params;

typedef enum e_states
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_states;

typedef struct s_philosopher
{
	unsigned int	id;
	pthread_t		*thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_states		state;
	unsigned int	times_eaten;
	unsigned int	time_last_eaten;

	t_params		params;
}	t_philo;

typedef struct s_table
{
	t_params		params;
	bool			start_routine;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_table;

// typedef struct s_table
// {
// 	unsigned int	philo_count;
// 	unsigned int	fork_count;
// 	unsigned int	time_to_die;
// 	unsigned int	time_to_eat;
// 	unsigned int	time_to_sleep;
// 	int				times_eaten;
// 	t_philo			*philos;
// }	t_table;

/*params.c*/

int		set_params(t_params *params, int argc, char **argv);

/*table.c*/

void	init_philos(t_params params, t_table *table);
int		init_table(t_table *table, t_params params);

/*utils.c*/

void	*ph_calloc(size_t count, size_t size);
int		ph_atoui(const char *str);

#endif