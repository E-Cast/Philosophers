/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:25:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/14 19:31:07 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

// Premade log messages.

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"

// Parameters

# define MAX_PHILO 200
# define MIN_TIME 60
# define PHILO_DELAY 50

typedef struct s_parameters
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
}	t_params;

// Philo

typedef pthread_mutex_t	t_mutex;

typedef enum e_state
{
	RUNNING,
	STOPPED,
	SATED
}	t_state;

typedef struct s_philo
{
	int			id;
	t_params	parameters;

	t_mutex		*mic_lock;
	t_state		*mic_state;
	t_mutex		*fork_l;
	t_mutex		*fork_r;
	t_mutex		*info_lock;

	t_state		state;
	long		time_last_eaten;
	int			times_eaten;
}	t_philo;

typedef struct s_data
{
	t_params	params;

	t_philo		*philos;
	pthread_t	*threads;
	t_mutex		mic_lock;
	t_state		mic_state;
	t_mutex		*forks;
	t_mutex		*info_lock;

	pthread_t	m_thread;
	t_mutex		m_lock;
}	t_data;

// Functions

void	free_data(t_data **data);
int		init_data(t_params params, t_data *data);

int		get_params(int argc, char **argv, t_params *params);

void	*start_monitor(void *arg);

void	*start_routine(void *arg);

void	wait_threads(int n, pthread_t *threads);
int		launch_threads(int n, t_data *data);

long	gettime_ms(void);
long	log_msg(t_philo *philo, char *msg);
void	wait_ms(int ms);

int		safe_mutex(t_mutex *mutex, int (mutex_func)(t_mutex *));
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

// Thread management //
// Launch patterns //
/*formula //
even philo_count:
t_to_die min == t_to_eat + t_to_sleep + (0.25 * philo_count) + 10
odd philo_count:
t_to_die min == (t_to_eat * 2) + t_to_sleep + (0.22 * philo_count) + 10
note: 0.22 is what works on my machine.
*/
// Make eating be the last message //
// Testing //
// Cleanup
// Comment as much as possible
// Make readme
// Final tests
// Push to git
/*
To do at 42
Norm
Tests
*/
/*
tools learnt:
Student's philo visualizer
fsanitize
ltrace
things learnt:
*/
#endif