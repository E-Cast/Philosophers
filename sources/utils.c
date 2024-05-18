/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:48:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 01:48:45 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_ms_time(t_time	*time)
{
	int	tmp;

	tmp = gettimeofday(&time->tv, NULL);
	time->ms = time->tv.tv_usec / 1000 + 1000 * time->tv.tv_sec;
	return (tmp);
}

void	log_msg(pthread_mutex_t *lock, bool *stop, int id, char *msg)
{
	t_time	time;

	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	else
		pthread_mutex_unlock(lock);
	get_ms_time(&time);
	printf("%li %i %s\n", time.ms, id, msg);
}
