/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/14 15:01:29 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)//tmp
{
	safe_mutex(philo->fork_l, pthread_mutex_lock);
	log_msg(-1, philo->id, philo->mic_lock, MSG_FORK);
	safe_mutex(philo->fork_r, pthread_mutex_lock);
	log_msg(-1, philo->id, philo->mic_lock, MSG_FORK);
	log_msg(-1, philo->id, philo->mic_lock, MSG_EAT);
	usleep(philo->parameters.time_to_eat * 1000);
	safe_mutex(philo->fork_l, pthread_mutex_unlock);
	safe_mutex(philo->fork_r, pthread_mutex_unlock);
}

void	*start_routine(void *arg)//tmp
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	int		i = philo->parameters.times_to_eat;
	if (i == 0)
		i = 1;
	// log_msg(-1, philo->id, "has woken up.");
	if (philo->id % 2 != 1)
		usleep(PHILO_DELAY);
	while (i-- > 0)
	{
		eat(philo);
		log_msg(-1, philo->id, philo->mic_lock, MSG_SLEEP);
		usleep(philo->parameters.time_to_sleep * 1000);
		log_msg(-1, philo->id, philo->mic_lock, MSG_THINK);
	}
	return (NULL);
}
