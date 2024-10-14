/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/14 16:14:28 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	eat(t_philo *philo)//tmp
{
	safe_mutex(philo->fork_l, pthread_mutex_lock);
	// check if continue
	log_msg(-1, philo, MSG_FORK);
	safe_mutex(philo->fork_r, pthread_mutex_lock);
	// check if continue
	log_msg(-1, philo, MSG_FORK);
	log_msg(-1, philo, MSG_EAT);
	// update time_last eaten
	mssleep(philo->parameters.time_to_eat);
	safe_mutex(philo->fork_l, pthread_mutex_unlock);
	safe_mutex(philo->fork_r, pthread_mutex_unlock);
}

// void	recursive_loop(t_philo *philo)
// {
// 	// /*
// 	if (philo->status != RUNNING)
// 		(void) philo;//unlock mutexes and return;
// 	eat(philo);
// 	if (philo->status != RUNNING)
// 		(void) philo;//unlock mutexes and return;
// 	log_msg(-1, philo->id, philo->mic_lock, MSG_SLEEP);
// 	mssleep(philo->parameters.time_to_sleep);//
// 	if (philo->status != RUNNING)
// 		(void) philo;//unlock mutexes and return;
// 	log_msg(-1, philo->id, philo->mic_lock, MSG_THINK);
// 	recursive_loop(philo);
// 	// */
// 	(void) philo;
// }

void	*start_routine(void *arg)//tmp
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	int		i = philo->parameters.times_to_eat;//
	if (i == 0)//
		i = 1;//
	// printf("id: %i, time last eaten: %li\n", philo->id, philo->time_last_eaten);//
	if (philo->id % 2 != 1)//test different start patterns
	{
		log_msg(-1, philo, MSG_THINK);
		usleep(PHILO_DELAY);
	}
	while (i-- > 0)
	{
		eat(philo);
		log_msg(-1, philo, MSG_SLEEP);
		mssleep(philo->parameters.time_to_sleep);
		log_msg(-1, philo, MSG_THINK);
	}
	// recursive_loop(philo);
	return (NULL);
}
