/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 11:37:57 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	terminate_all(t_data *data)
{
	int		index;

	safe_mutex(&data->mic_lock, pthread_mutex_lock);
	data->mic_state = STOPPED;
	safe_mutex(&data->mic_lock, pthread_mutex_unlock);

	index = 0;
	while (index < data->params.philo_count)
	{
		safe_mutex(data->philos[index].info_lock, pthread_mutex_lock);
		data->philos[index].state = STOPPED;
		safe_mutex(data->philos[index].info_lock, pthread_mutex_unlock);
		index++;
	}
	index = 0;
	while (index < data->params.philo_count)
		pthread_join(data->threads[index++], NULL);
	pthread_join(data->l_thread, NULL);
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

	if (get_params(argc, argv, &params) == -1)
		return (-1);
	if (params.philo_count == 1)
	{
		printf("%li 1 %s\n", gettime_ms(), MSG_FORK);
		wait_ms(params.time_to_die);
		printf("%li 1 %s\n", gettime_ms(), MSG_DIE);
		return (0);
	}
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL || init_data(params, data) == -1)
		return (-1);
	if (launch_threads(params.philo_count, data) == -1)
		return (free_data(&data), -1);
	recursive_monitor(data);
	terminate_all(data);
	return (free_data(&data), 0);
}
