/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 10:03:57 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	solo_philo(int time_to_sleep)
{
	long	time;

	time = gettime_ms();
	printf("%li 1 %s\n", time, MSG_FORK);
	mssleep(time_to_sleep);
	time = gettime_ms();
	printf("%li 1 %s\n", time, MSG_DIE);
}

int	main(int argc, char **argv)///make sure to check the return of every function and add error messages
{
	t_params	params;
	t_data		*data;

	if (argc < 5)
		return (printf("Error: too few arguments\n"), -1);
	if (get_params(argc, argv, &params) == -1)
		return (-1);
	if (params.philo_count == 1)
		return (solo_philo(params.time_to_die), -1);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (printf("Error: allocation failed.\n"), -1);
	if (init_data(params, data) == -1)
		return (-1);

	if (launch_threads(params.philo_count, data->threads, data->philos) == -1)
		return (free_data(&data), -1);
	//launch monitor
	pthread_create(&data->m_thread, NULL, start_monitor, data);//

	wait_threads(params.philo_count, data->threads);
	pthread_join(data->m_thread, NULL);
	return (free_data(&data), 0);
}
