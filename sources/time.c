/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:56:28 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 09:10:13 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Returns the current time in milliseconds.
 * 
 * @retval Timestamp in milliseconds on success.
 * @retval -1 on error.
 */
long	gettime_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("Error: failed to fetch time.\n"), -1);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

/**
 * @brief Logs a message to the terminal in the format 
 * 	"timestamp_in_ms ID message"
 * 
 * @param time Timestamp to log the message at, if -1 current time will be used.
 * @param ID ID to log the message under.
 * @param msg Message to be logged.
 * @retval 0 on success.
 * @retval -1 on error.
 */
int	log_msg(long time, t_philo *philo, char *msg)
{
	safe_mutex(philo->mic_lock, pthread_mutex_lock);
	if (time == -1)
		time = gettime_ms();
	if (time == -1)
		return (safe_mutex(philo->mic_lock, pthread_mutex_unlock), -1);
	if (0 > printf("%li %i %s\n", time, philo->id, msg))
		return (safe_mutex(philo->mic_lock, pthread_mutex_unlock), -1);
	safe_mutex(philo->mic_lock, pthread_mutex_unlock);
	return (0);
}

/**
 * @brief Suspends the calling thread's execution for ms milliseconds. 
 * 
 * @param ms How long to suspend execution for.
 * @retval 0 on success.
 * @retval -1 on error.
 */
int	mssleep(int ms)
{
	return (usleep(ms * 1000));
}
