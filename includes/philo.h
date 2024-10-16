/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:25:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 13:22:11 by ecastong         ###   ########.fr       */
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

typedef struct s_philo
{
	int			id;
	t_params	parameters;

	t_mutex		*mic_lock;
	int			*mic_status;
	t_mutex		*fork_l;
	t_mutex		*fork_r;
	t_mutex		*info_lock;//

	int			status;
	long		time_last_eaten;
	int			times_eaten;
}	t_philo;

# define RUNNING 1//use enum?                                                         //
# define STOP 2
# define SATED 3

typedef struct s_data
{
	t_params	params;

	t_philo		*philos;
	pthread_t	*threads;
	t_mutex		mic_lock;
	int			mic_status;
	t_mutex		*forks;
	t_mutex		*info_lock;

	pthread_t	m_thread;
}	t_data;

// Functions

void	free_data(t_data **data);
int		init_data(t_params params, t_data *data);

int		get_params(int argc, char **argv, t_params *params);

// monitor.c

void	*start_routine(void *arg);

void	wait_threads(int n, pthread_t *threads);
int		launch_threads(int n, pthread_t *threads, t_philo *philos);

long	gettime_ms(void);
int		log_msg(long time, t_philo *philo, char *msg);
int		mssleep(int ms);

int		safe_mutex(t_mutex *mutex, int (mutex_func)(t_mutex *));
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);




void	*start_monitor(void *arg);

/*

static int	check_status(t_philo *philo)
{
	int	status;

	safe_mutex(philo->info_lock, pthread_mutex_lock);
	status = philo->status;
	safe_mutex(philo->info_lock, pthread_mutex_unlock);

	return (status);
}

int	eaten_check(t_philo *philo_arr, t_params params)
{
	int		index;
	t_philo	*philo;

	index = 0;
	while (index < params.philo_count)
	{
		philo = &philo_arr[index++];
		safe_mutex(philo->info_lock, pthread_mutex_lock);
		if (philo->status == STOP)
			return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
		if (philo->status != SATED)
		{
			if (philo->times_eaten >= params.times_to_eat)
				philo->status = SATED;
			else
				return (safe_mutex(philo->info_lock, pthread_mutex_unlock), 0);
		}
		safe_mutex(philo->mic_lock, pthread_mutex_lock);
		if (!(index < params.philo_count))
			*philo->mic_status = STOP;
		safe_mutex(philo->mic_lock, pthread_mutex_unlock);
		safe_mutex(philo->info_lock, pthread_mutex_unlock);
	}
	return (-1);
}
data race caused by passing the philo pointer instead of a copy of philo to check status, solved it by passing it a t_philo instead of a t_philo *
*/
#endif