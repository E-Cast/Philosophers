/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:44 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 15:22:54 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>//
# include <stdlib.h>//
# include <stdio.h>//
# include <unistd.h>//

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

typedef struct timeval	t_time;

typedef struct s_supervisor_shared
{
	t_params		params;
	int				id;
	pthread_mutex_t	*stop_lock;
	bool			*stop;

	pthread_mutex_t	lock;
	t_time			time_last_eaten;
	bool			eating;//
	bool			alive;
}	t_super;

// typedef enum s_state
// {
// 	THINKING,
// 	EATING,
// 	SLEEPING
// }	t_state;

typedef struct s_philosopher_shared
{
	t_params		params;
	int				id;
	pthread_mutex_t	*stop_lock;
	bool			*stop;

	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;

	pthread_mutex_t	lock;
	bool			can_eat;
	bool			eating;
	bool			alive;

	t_super			super;
}	t_philo;

typedef struct s_table
{
	t_philo			philo;
	pthread_mutex_t	fork;
	pthread_t		thread;
}	t_table;

typedef struct s_program_data
{
	t_table			*table;

	t_params		params;
	pthread_t		thread;

	pthread_mutex_t	stop_lock;
	bool			stop;
}	t_data;

/*init.c*/

int		make_philo(t_data *data, t_params params, int index);
int		make_super(t_data *data, int index, t_params params);
int		init_table(t_data *data, t_params params);

/*params.c*/

int		check_arg_count(int argc);
int		ft_atoi(const char *str);
int		check_params(t_params *p, int argc);
int		set_params(t_params *params, int argc, char **argv);

/*philo.c*/

void	print_action(t_philo *philo, suseconds_t time, char *action);
void	dine(t_philo *philo);
void	*philo_start(void *arg);

/*supervisor.c*/

void	kill_philo(t_super *super, t_time time);
void	*supervisor(void *arg);

#endif