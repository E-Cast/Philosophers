/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:48:41 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 14:54:42 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philo(t_super *super, t_time time)
{
	pthread_mutex_lock(&super->lock);
	super->alive = false;
	pthread_mutex_unlock(&super->lock);
	pthread_mutex_lock(super->stop_lock);
	if (*super->stop == false)
	{
		*super->stop = true;
		pthread_mutex_unlock(super->stop_lock);
		printf("%li %i died\n", time.tv_usec, super->id);
	}
	else
		pthread_mutex_unlock(super->stop_lock);
}

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
		pthread_mutex_unlock(&super->lock);
		if (time.tv_usec - time_last_eaten.tv_usec >= super->params.time_to_die)
			return (kill_philo(super, time), NULL);
		// pthread_mutex_lock(super->stop_lock);
		// if (*super->stop == true)
		// {
		// 	pthread_mutex_lock(&super->lock);
		// 	super->alive = false;
		// 	pthread_mutex_unlock(&super->lock);
		// 	pthread_mutex_unlock(super->stop_lock);
		// 	return (NULL);
		// }
		// pthread_mutex_unlock(super->stop_lock);
	}
}
