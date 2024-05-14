/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 14:48:52 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dine(void *arg)
{
	t_philo		*philo;
	t_time		time;
	pthread_t	thread;
	bool		alive;

	philo = (t_philo *)arg;
	alive = true;
	pthread_mutex_lock(philo->super.stop_lock);
	if (*philo->super.stop == true)
		alive = false;
	pthread_mutex_unlock(philo->super.stop_lock);
	if (alive)
	{
		pthread_mutex_lock(&philo->super.lock);
		gettimeofday(&time, NULL);
		philo->super.time_last_eaten = time;
		pthread_mutex_unlock(&philo->super.lock);
		printf("%li %i is thinking\n", time.tv_usec, philo->id);
		if (pthread_create(&thread, NULL, supervisor, &philo->super) != 0)//
			return (NULL);
	}
	// pthread_mutex_lock(&philo->super.lock);
	// gettimeofday(&time, NULL);
	// philo->super.time_last_eaten = time;
	// pthread_mutex_unlock(&philo->super.lock);
	// printf("%li %i is thinking\n", time.tv_usec, philo->id);
	// if (pthread_create(&thread, NULL, supervisor, &philo->super) != 0)//
	// 	return (NULL);
	while (alive)
	{
		pthread_mutex_lock(&philo->super.lock);
		if (philo->super.alive == false)
			alive = false;
		pthread_mutex_unlock(&philo->super.lock);
		if (alive == false)
			break ;
	}
	pthread_join(thread, NULL);
	return (arg);
}
