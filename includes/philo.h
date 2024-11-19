/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:25:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 06:55:18 by ecastong         ###   ########.fr       */
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

/**
 * @brief Premade log message for when a philosopher takes a fork.
 */
# define MSG_FORK "has taken a fork"
/**
 * @brief Premade log message for when a philosopher starts eating.
 */
# define MSG_EAT "is eating"
/**
 * @brief Premade log message for when a philosopher starts sleeping.
 */
# define MSG_SLEEP "is sleeping"
/**
 * @brief Premade log message for when a philosopher starts thinking.
 */
# define MSG_THINK "is thinking"
/**
 * @brief Premade log message for when a philosopher dies.
 */
# define MSG_DIE "died"

typedef enum e_messages_id
{
	ID_FORK,
	ID_EAT,
	ID_SLEEP,
	ID_THINK,
	ID_DIE
}	t_msg_id;

/**
 * @brief Maximum number of philosophers the program supports.
 */
# define MAX_PHILO 200
/**
 * @brief Minimum time for time_to_die, time_to_eat, and time_to_sleep.
 */
# define MIN_TIME 60
/**
 * @brief How many microseconds wait_ms sleeps in between gettimeofday calls.
 * A higher number makes wait_ms less precise but also less ressource intensive.
 * Testing shows 100 to be the minimum value.
 */
# define WAIT_ACCURACY 500

/**
 * @brief Struct containing the user defined parameters.
 * 
 * @param philo_count Number of philosophers to simulate.
 * @param time_to_die Time allowed to a philosopher to go without
 * eating before starving.
 * @param time_to_eat Time a philosopher should take to eat.
 * @param time_to_sleep Time a philosopher should take to sleep.
 * @param times_to_eat Number of times every philosopher needs to
 * eat before the simulation stops.
 */
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

/**
 * @brief Enum of the program or philosophers' states:
 *
 * @param RUNNING The program or philosopher is running normally.
 * @param STOPPED The program or philosopher is stopped or should be stopping.
 * @param SATED The philosopher is running normally and has eaten at least
 * as many times as times_to_eat.///////////////////////////////////////////////////////////////////I think sated might be unecessary, which would make the enum itself unecessary
 */
typedef enum e_state
{
	RUNNING,
	STOPPED,
	SATED
}	t_state;

typedef struct s_node
{
	long			timestamp;
	int				id;
	// const char		*message;
	t_msg_id		message;
	struct s_node	*next;
}	t_node;

/**
 * @brief Struct containing all the external and shared data a philosopher has.
 * 
 * @param id The philosopher's ID.
 * @param params A copy of the struct containing the user defined parameters.
 * @param mic_lock The mutex controlling which thread can log messages to the
 * terminal and access related variables.
 * @param mic_state The t_state enum controlling whether or not threads are
 * allowed to log messages.
 * @param fork_l The mutex representing the fork to the left of the philosopher.
 * @param fork_r The mutex representing the fork to the right of the philosopher.
 * @param info_lock The mutex protexting the variables a philospher shares with
 * the t_data struct.
 * @param state The t_state enum representing the philosopher's current state.
 * @param time_last_eaten The last time the philosopher ate.
 * @param times_eaten The number of time the philosopher ate.
 */
typedef struct s_philo
{
	int			id;
	t_params	params;

	t_mutex		*mic_lock;
	t_state		*mic_state;
	t_node		**backlog;
	t_mutex		*fork_l;
	t_mutex		*fork_r;
	t_mutex		*info_lock;

	t_state		state;
	long		time_last_eaten;
	int			times_eaten;
}	t_philo;

/**
 * @brief Struct containing all the external and shared data a philosopher has.
 * 
 * @param params The struct containing the user defined parameters.
 * @param philos The array containing every t_philo structs.
 * @param threads The array containing every threads.
 * @param mic_lock The mutex controlling which thread can log messages to the
 * terminal and access related variables.
 * @param mic_state The t_state enum controlling whether or not threads are
 * allowed to log messages.
 * @param forks The array containing every fork mutex.
 * @param info_lock The array of containing every philosopher's info_lock mutex.
 *
 * @param m_thread The monitor's thread.
 * @param times_eaten The number of time the philosopher ate.
 */
typedef struct s_data
{
	t_params	params;

	t_philo		*philos;
	pthread_t	*threads;
	t_mutex		mic_lock;
	t_state		mic_state;
	t_node		**backlog;
	t_mutex		*forks;
	t_mutex		*info_lock;

	pthread_t	m_thread;
	pthread_t	l_thread;
}	t_data;

// Functions

void	free_data(t_data **data);
int		init_data(t_params params, t_data *data);

int		get_params(int argc, char **argv, t_params *params);

void	*start_monitor(void *arg);

void	*start_routine(void *arg);

void	wait_threads(int n, t_data *data);
int		launch_threads(int n, t_data *data);

long	gettime_ms(void);
long	log_msg(t_philo *philo, long time, t_msg_id message);
void	wait_ms(int ms);

int		safe_mutex(t_mutex *mutex, int (mutex_func)(t_mutex *));
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);


void	*start_logger(void *arg);
int		clear_list(t_node **list);
int		new_node(t_node **list, long time, int id, t_msg_id msg);

/*	Formula:
If: time_to_eat <= time_to_sleep
	Then: Minimum time_to_die == time_to_eat + time_to_sleep + 10;
Else if: philo count is even
	Then: Minimum time_to_die == time_to_eat * 2 + 10;
Else:
	Then: Minimum time_to_die == time_to_eat * 3 + 10;

Minimum time_to_die == time_to_eat + time_to_sleep + 10;
Else if time_to_eat <= time_to_sleep
Minimum time_to_die == time_to_eat * 2 + time_to_sleep + 10;
Else
Minimum time_to_die == time_to_eat * 3 + 10;

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
sleep funcs being unreliable
buffering (buffer and my own)

challenges faced:
data races
having the last message be a death or eating
terminal buffer/scrolling
unreliable sleep
*/
#endif