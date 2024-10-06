/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 07:42:33 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/06 08:27:45 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Returns the current time in milliseconds.
 * 
 * @retval timestamp in milliseconds on success.
 * @retval ERROR on failure.
 */
long	gettime_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ERROR);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

/**
 * @brief Logs a message to the terminal in the format 
 * "timestamp_in_ms ID message"
 * 
 * @param ID ID to log the message under.
 * @param msg Message to be logged.
 * @retval SUCCESS on success.
 * @retval ERROR on failure.
 */
int	log_msg(int ID, const char *msg)
{
	long	ms;

	ms = gettime_ms();
	if (ms == ERROR)
		return (ERROR);
	if (0 > printf("%li %i %s\n", ms, ID, msg))
		return (ERROR);
	return (SUCCESS);
}
