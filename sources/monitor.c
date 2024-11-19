/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:32:50 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 10:53:58 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* @brief Checks to see if a philo has starved by comparing the 
 * time it last ate to the current time.
 * 
 * @param philo_arr Array containing all the philosophers.
 * @param params Struct containing the user defined parameters.
 * @retval 0 if no philo has starved.
 * @retval -1 if a philo has starved.
 */
int	monitor_starvation(t_philo *philo_arr, t_params params)
{
	int		index;
	t_philo	*philo;
	long	time;

	index = 0;
	while (index < params.philo_count)
	{
		philo = &philo_arr[index++];
		safe_mutex(philo->info_lock, pthread_mutex_lock);
		time = gettime_ms();
		if (philo->time_last_eaten != -1 && time - philo->time_last_eaten
			>= params.time_to_die)
		{
			safe_mutex(philo->mic_lock, pthread_mutex_lock);
			new_node(philo->backlog, time, philo->id, M_ID_DIE);
			*philo->mic_state = STOPPED;
			safe_mutex(philo->mic_lock, pthread_mutex_unlock);
			philo->state = STOPPED;
			return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
		}
		safe_mutex(philo->info_lock, pthread_mutex_unlock);
	}
	return (0);
}

/**
 * @brief Monitors philosophers and ensures that they stop if one starve,
 *  or if they all have eaten enough times.
 * 
 * @param arg t_data* struct as a void pointer.
 * @retval NULL.
 */
void	*start_monitor(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	safe_mutex(&data->mic_lock, pthread_mutex_lock);
	if (data->mic_state == STOPPED)
		return (NULL);
	safe_mutex(&data->mic_lock, pthread_mutex_unlock);
	while (monitor_starvation(data->philos, data->params) != -1)
		usleep(250);
	return (NULL);
}
