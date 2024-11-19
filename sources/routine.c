/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 12:38:03 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Makes the philosopher eat.
 * 
 * @param philo 
 */
static int	eat(t_philo *philo)
{
	safe_mutex(philo->fork_l, pthread_mutex_lock);
	log_msg(philo, 0, M_ID_FORK);
	safe_mutex(philo->fork_r, pthread_mutex_lock);
	log_msg(philo, 0, M_ID_FORK);
	safe_mutex(philo->info_lock, pthread_mutex_lock);
	if (philo->state == STOP)
	{
		safe_mutex(philo->fork_l, pthread_mutex_unlock);
		safe_mutex(philo->fork_r, pthread_mutex_unlock);
		return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
	}
	philo->time_last_eaten = log_msg(philo, 0, M_ID_EAT);
	if (philo->params.times_to_eat > 0)
		philo->times_eaten++;
	safe_mutex(philo->info_lock, pthread_mutex_unlock);
	wait_ms(philo->params.time_to_eat);
	safe_mutex(philo->fork_l, pthread_mutex_unlock);
	safe_mutex(philo->fork_r, pthread_mutex_unlock);
	safe_mutex(philo->info_lock, pthread_mutex_lock);
	if (philo->state == STOP)
		return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
	safe_mutex(philo->info_lock, pthread_mutex_unlock);
	return (0);
}

/**
 * @brief Repeatedly makes the philo eat, sleep, and think 
 * until it is given the stop signal.
 * 
 * @param philo Philosopher to make eat, sleep, and think.
 */
void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	safe_mutex(philo->info_lock, pthread_mutex_lock);
	if (philo->state == STOP)
		return (safe_mutex(philo->info_lock, pthread_mutex_unlock), NULL);
	safe_mutex(philo->info_lock, pthread_mutex_unlock);
	if (philo->id % 2 == 0)
	{
		log_msg(philo, 0, M_ID_THINK);
		usleep(1000);
	}
	while (1)
	{
		if (eat(philo) == -1)
			return (NULL);
		log_msg(philo, 0, M_ID_SLEEP);
		wait_ms(philo->params.time_to_sleep);
		safe_mutex(philo->info_lock, pthread_mutex_lock);
		if (philo->state == STOP)
			return (safe_mutex(philo->info_lock, pthread_mutex_unlock), NULL);
		safe_mutex(philo->info_lock, pthread_mutex_unlock);
		log_msg(philo, 0, M_ID_THINK);
	}
}