/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:55 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 11:22:49 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// /**
//  * @brief Ensures all threads have terminated before returning.
//  * 
//  * @param n Number of threads.
//  * @param threads Array of threads.
//  */
// void	wait_threads(int n, t_data *data)
// {
// 	int	index;

// 	index = 0;
// 	while (index < n)
// 	{
// 		pthread_join(data->threads[index], NULL);
// 		index++;
// 	}
// 	pthread_join(data->l_thread, NULL);
// }

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
	// wait_threads(n, data);
	return ;
}

/**
 * @brief Launches all the philosophers with an odd ID and
 * then all the even ones.
 * 
 * @param start_time Start time to assign to the philos.
 * @param n Number of philosophers.
 * @param data Struct containing the threads, arguments,
 * and additional program data.
 * @retval 0 on a success.
 * @retval -1 on a failure.
 */
static int	staggered_launch(long start_time, int n, t_data *data)
{
	pthread_t	*th_arr;
	t_philo		*philos;
	int			index;

	th_arr = data->threads;
	philos = data->philos;
	index = 0;
	while (index < n)
	{
		safe_mutex(philos[index].info_lock, pthread_mutex_lock);
		philos[index].time_last_eaten = start_time;
		safe_mutex(philos[index].info_lock, pthread_mutex_unlock);
		if (pthread_create(&th_arr[index], NULL, start_routine, &philos[index]))
			return (-1);
		index += 2;
		if (index >= n && index % 2 == 0)
			index = 1;
	}
	return (0);
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
	long	start_time;

	if (pthread_create(&data->l_thread, NULL, start_logger, data) != 0)
		return (manage_thread_failure(n, data), -1);
	start_time = gettime_ms();
	if (staggered_launch(start_time, n, data))
		return (manage_thread_failure(n, data), -1);
	return (0);
}
