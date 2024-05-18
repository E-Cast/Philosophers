/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 01:20:30 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*super(void *arg)
{
	t_super	*super;

	super = (t_super *)arg;
	return (NULL);
	(void) super;
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mp_lock);
	if (pthread_create(&philo->su_thread, NULL,
			super, &philo->super) != 0)
		return (NULL);
	pthread_mutex_unlock(&philo->mp_lock);
	pthread_mutex_lock(philo->start_lock);
	usleep(1);
	pthread_mutex_unlock(philo->start_lock);
	log_msg(philo->stop_lock, philo->stop, philo->id, "is thinking");

	pthread_join(philo->su_thread, NULL);
	return (NULL);
}
