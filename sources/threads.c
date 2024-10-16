/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:55 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 10:06:12 by ecastong         ###   ########.fr       */
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
 * @brief Sets the start time to the current time and launches all threads.
 * 
 * @param n Number of threads to launch.
 * @param data Struct containing the threads and the arguments for the routine.
 * @retval 0 on success.
 * @retval -1 on error.
 */
int	launch_threads(int n, pthread_t *threads, t_philo *philos)
{
	int		index;
	long	start_time;

	index = 0;
	start_time = gettime_ms();
	while (index < n)
	{
		philos[index].time_last_eaten = start_time;
		if (pthread_create(&threads[index], NULL,
				start_routine, &philos[index]))
			return (printf("Error: Failed to create thread.n"), -1);//
		usleep(10);
		index++;
	}
	return (0);
}
