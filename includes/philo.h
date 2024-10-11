/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:25:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/11 14:07:21 by ecastong         ###   ########.fr       */
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

// Return values.

# define ERROR -1
# define SUCCESS 0

// Premade log messages.

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

// Parameters

# define MAX_PHILO 200
# define MIN_TIME 60

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
	t_params	parameters;
	pthread_t	thread;
	int			id;

	t_mutex		*fork_l;
	t_mutex		*fork_r;
	t_mutex		*dead_lock;
	long		time_last_eaten;
	int			times_eaten;
	int			status;	
}	t_philo;

# define DEAD 0
# define THINKING 1
# define EATING 2 
# define SLEEPING 3 

// Functions

long	gettime_ms(void);
int		log_msg(long time, int ID, const char *msg);
int		ft_atoi(const char *str);
int		get_params(int argc, char **argv, t_params *params);
void	*ft_calloc(size_t count, size_t size);

#endif