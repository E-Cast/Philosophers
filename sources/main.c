/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 10:17:12 by ecastong         ###   ########.fr       */
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
// rename mic_loc to a more appropriate name for what it's used
// rename all the shared variables to add an easy to find prefix with search
// destroy the mutexes at the end
// bus error if I let it run for long enough
// do I even need a monitor thread? could the main just handle it?
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
	wait_threads(params.philo_count, data);
	return (free_data(&data), 0);
}
