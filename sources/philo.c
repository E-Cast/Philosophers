/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 02:37:12 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
{
	t_philo	*philo;
	// t_time	time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mp_lock); // so other philo is launched before this one is inited
	pthread_mutex_lock(&philo->super.sp_lock); // so super starts right after the philo 
	if (pthread_create(&philo->su_thread, NULL,
			super, &philo->super) != 0)
		return (NULL);
	pthread_mutex_unlock(&philo->mp_lock);
	pthread_mutex_lock(philo->start_lock); // so philo starts only after every philo is launched
	usleep(1000);
	pthread_mutex_unlock(philo->start_lock);
	get_ms_time(&philo->super.sp_t_last_ate);
	log_msg(philo->stop_lock, philo->stop, philo->id, "is thinking");
	pthread_mutex_unlock(&philo->super.sp_lock);

	pthread_join(philo->su_thread, NULL);
	return (NULL);
}
