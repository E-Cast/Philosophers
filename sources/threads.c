/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:55 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/19 10:13:26 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Ensures all threads have terminated before returning.
 * 
 * @param n Number of threads.
 * @param threads Array of threads.
 */
void	wait_threads(int n, pthread_t *threads)
{
	int	index;

	index = 0;
	while (index < n)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
}

/**
 * @brief Safely stops and waits every thread before returning.
 * 
 * @param n Number of threads.
 * @param threads Struct containing the threads and additional program data.
 */
static void	manage_thread_failure(int n, t_data *data)
{
	int		index;
	t_philo	*philo;

	safe_mutex(&data->mic_lock, pthread_mutex_lock);
	data->mic_state = STOPPED;
	safe_mutex(&data->mic_lock, pthread_mutex_unlock);
	printf("Error: Failed to create thread.\n");
	index = 0;
	while (index < n)
	{
		philo = &data->philos[index++];
		safe_mutex(philo->info_lock, pthread_mutex_lock);
		philo->state = STOPPED;
		safe_mutex(philo->info_lock, pthread_mutex_unlock);
	}
	safe_mutex(&data->m_lock, pthread_mutex_unlock);
	wait_threads(n, data->threads);
	return ;
}

/**
 * @brief Sets the start time to the current time and launches all threads.
 * 
 * @param n Number of threads to launch.
 * @param data Struct containing the threads, arguments for the routine, 
 * and additional program data.
 * @retval 0 on success.
 * @retval -1 on error.
 */
int	launch_threads(int n, t_data *data)
{
	int			index;
	long		start_time;
	pthread_t	*th_arr;
	t_philo		*philos;

	index = 0;
	safe_mutex(&data->m_lock, pthread_mutex_lock);
	if (pthread_create(&data->m_thread, NULL, start_monitor, data) != 0)
		return (manage_thread_failure(n, data), -1);
	th_arr = data->threads;
	philos = data->philos;
	start_time = gettime_ms();
	while (index < n)
	{
		philos[index].time_last_eaten = start_time;
		if (pthread_create(&th_arr[index], NULL, start_routine, &philos[index]))
			return (manage_thread_failure(n, data), -1);
		usleep(10);
		index++;
	}
	safe_mutex(&data->m_lock, pthread_mutex_unlock);
	return (0);
}
