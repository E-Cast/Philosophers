/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 13:22:37 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Retrieves and returns the a philo's status.
 * 
 * @param info_lock The mutex protecting the philo's status.
 * @param philo_status The philo's status variable shared with other threads.
 * @retval The philo's status as an int.
 */
// static int	check_status(t_mutex *info_lock, int *philo_status)
// {
// 	int	status;

// 	safe_mutex(info_lock, pthread_mutex_lock);
// 	status = *philo_status;
// 	safe_mutex(info_lock, pthread_mutex_unlock);

// 	return (status);
// }
static int	check_status(t_philo philo)
{
	int	status;

	safe_mutex(philo.info_lock, pthread_mutex_lock);
	status = philo.status;
	safe_mutex(philo.info_lock, pthread_mutex_unlock);

	return (status);
}

/**
 * @brief Makes the philosopher eat.
 * 
 * @param philo 
 */
static int	eat(t_philo *philo)
{
	long	time;

	safe_mutex(philo->fork_l, pthread_mutex_lock);
	log_msg(-1, philo, MSG_FORK);
	safe_mutex(philo->fork_r, pthread_mutex_lock);
	log_msg(-1, philo, MSG_FORK);
	if (check_status(*philo) == STOP)
		return (-1);
	safe_mutex(philo->info_lock, pthread_mutex_lock);
	if (philo->status == STOP)
		return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
	time = gettime_ms();
	philo->time_last_eaten = time;
	log_msg(time, philo, MSG_EAT);
	philo->times_eaten++;
	safe_mutex(philo->info_lock, pthread_mutex_unlock);
	mssleep(philo->parameters.time_to_eat);
	return (0);
}

/**
 * @brief Repeatedly makes the philo eat, sleep, and think 
 * until it is given the stop signal.
 * 
 * @param philo Philosopher to make eat, sleep, and think.
 */
static void	recursive_loop(t_philo *philo)
{
	if (eat(philo) == -1)
	{
		safe_mutex(philo->fork_l, pthread_mutex_unlock);
		safe_mutex(philo->fork_r, pthread_mutex_unlock);
		return ;
	}
	safe_mutex(philo->fork_l, pthread_mutex_unlock);
	safe_mutex(philo->fork_r, pthread_mutex_unlock);
	if (check_status(*philo) == STOP)
		return ;
	log_msg(-1, philo, MSG_SLEEP);
	mssleep(philo->parameters.time_to_sleep);
	if (check_status(*philo) == STOP)
		return ;
	log_msg(-1, philo, MSG_THINK);
	if (check_status(*philo) == STOP)
		return ;
	recursive_loop(philo);
}

/**
 * @brief Executes the philosopher's routine until it receives the stop signal.
 * 
 * @param arg t_philo struct as a void *.
 * @retval NULL.
 */
void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		log_msg(-1, philo, MSG_THINK);
		usleep(PHILO_DELAY);
	}
	recursive_loop(philo);
	return (NULL);
}
