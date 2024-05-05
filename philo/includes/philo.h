/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:44 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/05 12:21:04 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <string.h>
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

// typedef enum e_states
// {
// 	EATING,
// 	SLEEPING,
// 	THINKING
// }	t_states;

// typedef struct s_philosopher
// {
// 	unsigned int	id;
// 	pthread_t		thread;
// 	t_states		state;
// }	t_philo;

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

int	set_params(t_params *params, int argc, char **argv);

/*utils.c*/

int	ph_atoui(const char *str);

#endif