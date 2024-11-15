/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:56:28 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/15 00:30:50 by ecastong         ###   ########.fr       */
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
 * @param ID ID to log the message under.
 * @param msg Message to be logged.
 * @retval The timestamp the message was logged with on success.
 * @retval -1 on error.
 */
long	log_msg(t_philo *philo, char *msg)
{
	long	time;

	safe_mutex(philo->mic_lock, pthread_mutex_lock);
	if (*philo->mic_state == STOPPED)
		return (safe_mutex(philo->mic_lock, pthread_mutex_unlock), 0);
	time = gettime_ms();
	if (time == -1)
		return (safe_mutex(philo->mic_lock, pthread_mutex_unlock), -1);
	if (0 > printf("%li %i %s\n", time, philo->id, msg))
		return (safe_mutex(philo->mic_lock, pthread_mutex_unlock), -1);
	safe_mutex(philo->mic_lock, pthread_mutex_unlock);
	return (time);
}

/**
 * @brief Waits for the specified amount of time.
 * 
 * @param ms How long to wait for.
 */
void	wait_ms(int ms)
{
	long	target_time;
	long	current_time;

	target_time = gettime_ms() + ms;
	current_time = 0;
	while (current_time < target_time)
	{
		current_time = gettime_ms();
		usleep(500);
	}
}
