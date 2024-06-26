/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:44 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 01:58:33 by ecastong         ###   ########.fr       */
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

typedef struct time
{
	struct timeval	tv;
	long			ms;
}	t_time;

/*params*/

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

int		check_arg_count(int argc);
int		ft_atoi(const char *str);
int		check_params(t_params *p, int argc);
int		set_params(t_params *params, int argc, char **argv);

/*super*/

typedef struct s_supervisor_data
{
	t_params		params;
	int				id;
	pthread_mutex_t	*stop_lock;
	bool			*stop;

	pthread_mutex_t	sp_lock;
	bool			sp_alive;
	t_time			sp_t_last_ate;
}	t_super;

void	*super(void *arg);

/*philo*/

typedef struct s_philosopher_data
{
	t_params		params;
	int				id;
	pthread_mutex_t	*start_lock;
	pthread_mutex_t	*stop_lock;
	bool			*stop;

	pthread_t		ph_thread;
	pthread_t		su_thread;
	pthread_mutex_t	*can_eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;

	pthread_mutex_t	mp_lock;
	// bool			mp_alive;
	t_time			mp_t_last_ate;

	t_super			super;
}	t_philo;

void	*philo(void *arg);

/*table*/

typedef struct s_table
{
	// t_params		params;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	stop_lock;
	bool			stop;

	t_philo			*philo;
	pthread_mutex_t	*can_eat;
	pthread_mutex_t	*forks;
}	t_table;

int		make_super(t_philo *philo);
int		make_philo(t_table *table, t_params params, int index);
void	*ph_calloc(size_t count, size_t size);
int		make_arrays(t_table *table, t_params params);
t_table	*make_table(t_params params);

/*utils*/

int		get_ms_time(t_time	*time);
void	log_msg(pthread_mutex_t *lock, bool *stop, int id, char *msg);

/*tmp*/

t_table	*make_table(t_params params);
int		make_philo(t_table *table, t_params params, int index);

#endif