/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/16 19:11:02 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_msg(pthread_mutex_t *lock, bool *stop, int id, char msg)
{
	t_time	time;
	
	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	gettimeofday(&time, NULL);
	printf("%li %i %i\n", time, id, msg);
	pthread_mutex_unlock(lock);
}
