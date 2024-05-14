/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 14:34:20 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *arg)
{
	t_super		*super;
	t_time		time;
	t_time		time_last_eaten;

	super = (t_super *)arg;
	while (true)
	{
		pthread_mutex_lock(&super->lock);
		time_last_eaten = super->time_last_eaten;
		gettimeofday(&time, NULL);
		if (time.tv_usec - time_last_eaten.tv_usec >= super->params.time_to_die)
		{
			printf("%li %i died\n", time.tv_usec, super->id);
			super->alive = false;
			pthread_mutex_unlock(&super->lock);
			pthread_mutex_lock(super->stop_lock);
			*super->stop = true;
			pthread_mutex_unlock(super->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&super->lock);
		pthread_mutex_lock(super->stop_lock);
		if (*super->stop == true)
		{
			pthread_mutex_unlock(super->stop_lock);
			pthread_mutex_lock(&super->lock);
			super->alive = false;
			pthread_mutex_unlock(&super->lock);
			break ;
		}
		else
			pthread_mutex_unlock(super->stop_lock);
	}
	return (arg);
}

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
