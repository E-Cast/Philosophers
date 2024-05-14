/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 15:28:45 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_philos(void *arg)
{
	t_data	*data;
	int		index;
	int		jndex;

	data = (t_data *)arg;
	index = 0;
	while (index < data->params.philo_count)
	{
		if (pthread_create(&data->table[index].thread, NULL, philo_start,
				(void *)&data->table[index].philo) != 0)
			break ;
		index++;
		usleep(1);
	}
	jndex = 0;
	while (jndex < index)
		pthread_join(data->table[jndex++].thread, NULL);
	return (data);
}

void	monitor(t_table *table)
{
	t_philo	philo;

	philo = table[0].philo;
	pthread_mutex_lock(&philo.lock);
	philo.can_eat = true;
	pthread_mutex_unlock(&philo.lock);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (printf("Error: failed to alloc memory\n"), EXIT_FAILURE);
	if (set_params(&data->params, argc, argv) != 0)
		return (free(data), EXIT_FAILURE);
	if (init_table(data, data->params) == EXIT_FAILURE)
		return (free(data), EXIT_FAILURE);
	if (pthread_create(&data->thread, NULL, start_philos, (void *)data) != 0)
		return (printf("Error: failed to create thread\n"),
			free(data->table), free(data), EXIT_FAILURE);
	//coordinate threads
	monitor(data->table);
	// pthread_mutex_lock(&data->table->philo.lock);
	// data->table[0].philo.can_eat = true;
	// pthread_mutex_unlock(&data->table->philo.lock);
	//there should be no threads running by the time coordiate returns;
	pthread_join(data->thread, NULL);
	return (free(data->table), free(data), EXIT_SUCCESS);
}
