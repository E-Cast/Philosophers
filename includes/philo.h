/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:25:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 18:45:46 by ecastong         ###   ########.fr       */
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
# define MSG_DIE "died"

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

# define SILENT = 1;

typedef struct s_philo
{
	int			id;
	t_params	parameters;

	t_mutex		*mic_lock;
	t_state		*mic_state;
	t_mutex		*fork_l;
	t_mutex		*fork_r;
	t_mutex		*info_lock;//

	// int			status;
	t_state		state;
	long		time_last_eaten;
	int			times_eaten;
}	t_philo;

// # define RUNNING 1//use enum?                                                         //
// # define STOP 2
// # define SATED 3

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
}	t_data;

// Functions

void	free_data(t_data **data);
int		init_data(t_params params, t_data *data);

int		get_params(int argc, char **argv, t_params *params);

void	*start_monitor(void *arg);

void	*start_routine(void *arg);

void	wait_threads(int n, pthread_t *threads);
int		launch_threads(int n, pthread_t *threads, t_philo *philos);

long	gettime_ms(void);
int		log_msg(long time, t_philo *philo, char *msg);
int		mssleep(int ms);

int		safe_mutex(t_mutex *mutex, int (mutex_func)(t_mutex *));
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif