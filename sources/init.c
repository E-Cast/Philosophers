/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:45:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/11 12:58:31 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	thread_mutex_init(pthread_mutex_t *mutex, void *arg)
// {
// 	return (1);
// 	(void) mutex;
// 	(void) arg;
// }

int	make_philo(t_table **table, t_params params, int index)
{
	t_philo	philo;

	if (pthread_mutex_init(&philo.sup_lock, NULL) != 0)
		return (printf("Error: failed to init mutex\n"), EXIT_FAILURE);
	philo.params = params;
	philo.id = index + 1;
	philo.fork_l = &(*table)[index].fork;
	if (params.philo_count >= 1)
		philo.fork_r = NULL;
	else if (index + 1 == params.philo_count)
		philo.fork_r = &(*table)[0].fork;
	else
		philo.fork_r = &(*table)[index].fork;
	philo.lock = &(*table)[index].lock;
	philo.time_last_eaten = &(*table)[index].time_last_eaten;
	philo.can_eat = &(*table)[index].can_eat;
	philo.eating = &(*table)[index].eating;
	// philo.dead = &(*table)[index].dead;
	(*table)[index].philo = philo;
	return (EXIT_SUCCESS);
}

int	init_table(t_table **table, t_params params)
{
	int		index;

	*table = malloc((params.philo_count + 1) * sizeof(t_table));
	if (!(*table))
		return (printf("Error: failed to alloc memory\n"), EXIT_FAILURE);
	memset(*table, 0, params.philo_count + 1);
	index = 0;
	while (index < params.philo_count)
	{
		if (pthread_mutex_init(&(*table)[index].fork, NULL) != 0)
			return (free(*table), printf("Error: failed to init mutex\n"),
				EXIT_FAILURE);
		if (pthread_mutex_init(&(*table)[index].lock, NULL) != 0)
			return (free(*table), printf("Error: failed to init mutex\n"),
				EXIT_FAILURE);
		if (make_philo(table, params, index) == EXIT_FAILURE)
			return (free(*table), EXIT_FAILURE);
		(*table)[index].time_last_eaten = (t_time){.tv_sec = 0, .tv_usec = 0};
		(*table)[index].can_eat = false;
		(*table)[index].eating = false;
		(*table)[index].dead = false;
		index++;
	}
	return (EXIT_SUCCESS);
}
