/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:45:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/12 23:32:05 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	thread_mutex_init(pthread_mutex_t *mutex, void *arg)
// {
// 	return (1);
// 	(void) mutex;
// 	(void) arg;
// }

int	make_philo(t_data *data, t_params params, int index)
{
	t_philo	*philo;

	philo = &data->table[index].philo;
	philo->params = params;
	philo->id = index + 1;
	philo->fork_l = &data->table[index].fork;
	if (params.philo_count >= 1)
		philo->fork_r = NULL;
	else if (index + 1 == params.philo_count)
		philo->fork_r = &data->table[0].fork;
	else
		philo->fork_r = &data->table[index].fork;
	if (pthread_mutex_init(&philo->lock, NULL) != 0)
		return (printf("Error: failed to init mutex\n"), EXIT_FAILURE);
	philo->can_eat = false;
	philo->eating = false;
	philo->alive = true;
	philo->stop_lock = &data->stop_lock;
	philo->stop = &data->stop;
	return (EXIT_SUCCESS);
}

int	make_super(t_data *data, int index, t_params params)
{
	t_philo	*philo;

	philo = &data->table[index].philo;
	philo->super.params = params;
	philo->super.id = philo->id;
	if (pthread_mutex_init(&philo->super.lock, NULL) != 0)
		return (printf("Error: failed to init mutex\n"), EXIT_FAILURE);
	philo->super.time_last_eaten = (t_time){.tv_sec = 0, .tv_usec = 0};
	philo->super.eating = false;
	philo->super.alive = true;
	philo->super.stop_lock = &data->stop_lock;
	philo->super.stop = &data->stop;
	return (EXIT_SUCCESS);
}

int	init_table(t_data *data, t_params params)
{
	int				index;

	data->table = malloc((params.philo_count + 1) * sizeof(t_table));
	if (!data->table)
		return (printf("Error: failed to alloc memory\n"), EXIT_FAILURE);
	memset(data->table, 0, params.philo_count + 1);
	if (pthread_mutex_init(&data->stop_lock, NULL) != 0)
		return (printf("Error: failed to init mutex\n"),
			free(data->table), EXIT_FAILURE);
	data->stop = false;
	index = 0;
	while (index < params.philo_count)
	{
		if (pthread_mutex_init(&data->table[index].fork, NULL) != 0)
			return (printf("Error: failed to init mutex\n"),
				free(data->table), EXIT_FAILURE);
		if (make_philo(data, params, index) == EXIT_FAILURE)
			return (free(data->table), EXIT_FAILURE);
		if (make_super(data, index, params) == EXIT_FAILURE)
			return (free(data->table), EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}
