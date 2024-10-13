/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/13 13:20:28 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_philo(t_philo philo)
{
	printf("id:%i\n", philo.id);
	pthread_mutex_lock(philo.fork_l);
	printf("fork_l: valid\n");
	pthread_mutex_lock(philo.fork_r);
	printf("fork_r: valid\n");
	pthread_mutex_unlock(philo.fork_l);
	pthread_mutex_unlock(philo.fork_r);
	printf("last eaten:%li\n", philo.time_last_eaten);
	printf("times eaten:%i\n\n", philo.times_eaten);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;

	if (argc < 5)
		return (printf("Error: too few arguments\n"), ERROR);
	if (get_params(argc, argv, &params) == ERROR)
		return (ERROR);

	if (init_data(params, &data) == ERROR)
		return (ERROR);
	// launch all threads
	// 		free philo and return on error
	for (int i = 0; i < params.philo_count; i++)
		test_philo(data.philos[i]);
	free_data(&data);
	return (SUCCESS);
}
