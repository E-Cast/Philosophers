/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/18 22:29:41 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(int time_to_sleep)
{
	long	time;

	time = gettime_ms();
	printf("%li 1 %s\n", time, MSG_FORK);
	wait_ms(time_to_sleep);
	time = gettime_ms();
	printf("%li 1 %s\n", time, "died");
}

// make sure to check the return of every function and add error messages
// check for data races
// check for memory leaks
// try launching monitor after all the threads
// rename mic_loc to a more appropriate name for what it's used
int	main(int argc, char **argv)
{
	t_params	params;
	t_data		*data;

	if (argc < 5)
		return (printf("Error: too few arguments\n"), -1);
	if (get_params(argc, argv, &params) == -1)
		return (-1);
	if (params.philo_count == 1)
		return (one_philo(params.time_to_die), 0);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (printf("Error: allocation failed.\n"), -1);
	if (init_data(params, data) == -1)
		return (-1);
	if (launch_threads(params.philo_count, data) == -1)
		return (free_data(&data), -1);
	wait_threads(params.philo_count, data->threads, data->m_thread);
	return (free_data(&data), 0);
}

/*
Philo:
	locks mic lock
	assembles message
	adds message as a new node to the end of the buffer linked list
	unlocks mic lock

Buffer:
	locks mic lock
	copies first message of the linked list
	sets the string to null and frees it
	deletes the first node and sets the second one as first
	unlocks mic lock
	checks if message signals the end (death message or eating message which makes all philos sated)
	writes message to terminal

advantage:
	1. The program does not have to wait for the terminal buffer to execute things.
	2. It doesn't have to silence the philos as fast since the buffer can stop printing in the middle of execution. Thus making the philos do less checks and execute faster.

notes:
	Messages can either be a string the buffer simlply has to print to the terminal, or a struct containing the timestamp, id, and message type.
*/