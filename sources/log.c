/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 17:57:32 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_think(pthread_mutex_t *lock, bool *stop, suseconds_t time, int id)
{
	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	printf("%li %i is thinking\n", time, id);
	pthread_mutex_unlock(lock);
}

void	log_fork(pthread_mutex_t *lock, bool *stop, suseconds_t time, int id)
{
	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	printf("%li %i has taken a fork\n", time, id);
	pthread_mutex_unlock(lock);
}

void	log_eat(pthread_mutex_t *lock, bool *stop, suseconds_t time, int id)
{
	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	printf("%li %i is eating\n", time, id);
	pthread_mutex_unlock(lock);
}

void	log_sleep(pthread_mutex_t *lock, bool *stop, suseconds_t time, int id)
{
	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	printf("%li %i is sleeping\n", time, id);
	pthread_mutex_unlock(lock);
}

void	log_die(pthread_mutex_t *lock, bool *stop, suseconds_t time, int id)
{
	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	printf("%li %i died\n", time, id);
	pthread_mutex_unlock(lock);
}
