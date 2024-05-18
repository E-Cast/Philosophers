/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 01:48:08 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*super(void *arg)
{
	t_super	*super;
	// t_time	time;
	// t_time	t_last_ate;

	super = (t_super *)arg;
	pthread_mutex_lock(&super->sp_lock);
	pthread_mutex_unlock(&super->sp_lock);
	// while (true)
	// {
	// 	pthread_mutex_lock(&super->sp_lock);
	// 	t_last_ate = super->sp_t_last_ate;
	// 	pthread_mutex_unlock(&super->sp_lock);
	// 	if (time_to_ms(time) - time_to_ms(t_last_ate) >= time_to_ms(t_last_ate))
	// }
	return (NULL);
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mp_lock); // so other philo is launched before this one is inited
	pthread_mutex_lock(&philo->super.sp_lock); // so super starts right after the philo 
	if (pthread_create(&philo->su_thread, NULL,
			super, &philo->super) != 0)
		return (NULL);
	pthread_mutex_unlock(&philo->mp_lock);
	pthread_mutex_lock(philo->start_lock); // so philo starts only after every philo is launched
	usleep(1);
	pthread_mutex_unlock(philo->start_lock);
	pthread_mutex_unlock(&philo->super.sp_lock);
	log_msg(philo->stop_lock, philo->stop, philo->id, "is thinking");

	pthread_join(philo->su_thread, NULL);
	return (NULL);
}
