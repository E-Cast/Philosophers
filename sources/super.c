/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:56:57 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 02:29:59 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	die(t_super *super)
{
	pthread_mutex_lock(super->stop_lock);
	*super->stop = true;
	pthread_mutex_unlock(super->stop_lock);
	super->sp_alive = false;
	log_msg(NULL, NULL, super->id, "died");
	return (false);
}

void	*super(void *arg)
{
	t_super	*super;
	bool	alive;
	t_time	time;

	super = (t_super *)arg;
	pthread_mutex_lock(&super->sp_lock);
	pthread_mutex_unlock(&super->sp_lock);
	alive = true;
	while (alive)
	{
		pthread_mutex_lock(&super->sp_lock);
		get_ms_time(&time);
		if (time.ms - super->sp_t_last_ate.ms >= super->params.time_to_die)
			alive = die(super);
		pthread_mutex_unlock(&super->sp_lock);
		pthread_mutex_lock(super->stop_lock);
		if (*super->stop == true)
		{
			pthread_mutex_lock(&super->sp_lock);
			alive = false;
			pthread_mutex_unlock(&super->sp_lock);
		}
		pthread_mutex_unlock(super->stop_lock);
	}
	return (NULL);
}
