/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/13 18:59:46 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	test_philo(t_philo philo)
// {
// 	printf("id:%i\n", philo.id);
// 	pthread_mutex_lock(philo.start_lock);
// 	printf("start_lock: valid\n");
// 	pthread_mutex_unlock(philo.start_lock);
// 	pthread_mutex_lock(philo.fork_l);
// 	printf("fork_l: valid\n");
// 	pthread_mutex_lock(philo.fork_r);
// 	printf("fork_r: valid\n");
// 	pthread_mutex_unlock(philo.fork_l);
// 	pthread_mutex_unlock(philo.fork_r);
// 	printf("last eaten:%li\n", philo.time_last_eaten);
// 	printf("times eaten:%i\n\n", philo.times_eaten);
// }

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	printf("id: %i\n", philo->id);
	return (NULL);
}

// int	test_pthread_create(pthread_t *thread, t_philo *philo, int index)
// {
// 	if (index == 7)
// 		return (ERROR);
// 	pthread_create(thread, NULL, start_routine, philo);
// 	return (SUCCESS);
// }

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

int	launch_threads(int n, t_data data)
{
	int	index;

	index = 0;
	pthread_mutex_lock(data.start_lock);
	while (index < n)
	{
		// if (test_pthread_create(&data.threads[index], &data.philos[index], index) != 0)
		if (pthread_create(&data.threads[index], NULL, start_routine, &data.philos[index]))
			return (printf("test\n"), ERROR);
		usleep(10);
		index++;
	}
	pthread_mutex_unlock(data.start_lock);
	wait_threads(n, data.threads);
	return (SUCCESS);
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

	if (launch_threads(params.philo_count, data))
		return (free_data(&data), ERROR);
	// launch all threads
	// 		free philo and return on error

	// for (int i = 0; i < params.philo_count; i++)
	// 	test_philo(data.philos[i]);
	free_data(&data);
	return (SUCCESS);
}
