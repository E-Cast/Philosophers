/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/18 21:43:04 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Retrieves and returns the philo's current state.
 * 
 * @param info_lock The mutex protecting the philo's status.
 * @param philo The philosopher to extract the state of.
 * @retval The philo's status as an int.
 */
static int	extract_state(t_philo philo)
{
	int	state;

	safe_mutex(philo.info_lock, pthread_mutex_lock);
	state = philo.state;
	safe_mutex(philo.info_lock, pthread_mutex_unlock);
	return (state);
}

/**
 * @brief Makes the philosopher eat.
 * 
 * @param philo 
 */
static int	eat(t_philo *philo)
{
	safe_mutex(philo->fork_l, pthread_mutex_lock);
	log_msg(philo, MSG_FORK);
	safe_mutex(philo->fork_r, pthread_mutex_lock);
	log_msg(philo, MSG_FORK);
	if (extract_state(*philo) == STOPPED)
		return (-1);
	safe_mutex(philo->info_lock, pthread_mutex_lock);
	if (philo->state == STOPPED)
		return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
	philo->time_last_eaten = log_msg(philo, MSG_EAT);
	philo->times_eaten++;
	safe_mutex(philo->info_lock, pthread_mutex_unlock);
	wait_ms(philo->params.time_to_eat);
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
	if (extract_state(*philo) == STOPPED)
		return ;
	log_msg(philo, MSG_SLEEP);
	wait_ms(philo->params.time_to_sleep);
	if (extract_state(*philo) == STOPPED)
		return ;
	log_msg(philo, MSG_THINK);
	if (extract_state(*philo) == STOPPED)
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
	if (extract_state(*philo) == STOPPED)
		return (NULL);
	if (philo->id % 2 == 0)
	{
		log_msg(philo, MSG_THINK);
		usleep(1000);
	}
	recursive_loop(philo);
	return (NULL);
}
