/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:45:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/11 14:16:28 by ecastong         ###   ########.fr       */
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
	t_philo	*philo;

	philo = (*table)[index].philo;
	philo->params = params;
	philo->id = index + 1;
	philo->fork_l = &(*table)[index].fork;
	if (params.philo_count >= 1)
		philo->fork_r = NULL;
	else if (index + 1 == params.philo_count)
		philo->fork_r = &(*table)[0].fork;
	else
		philo->fork_r = &(*table)[index].fork;
	if (pthread_mutex_init(&philo->lock, NULL) != 0)
		return (printf("Error: failed to init mutex\n"), EXIT_FAILURE);//
	philo->can_eat = false;
	philo->eating = false;
	philo->alive = false;
	philo->super->params = params;
	philo->super->id = index +1;
	if (pthread_mutex_init(&philo->super->lock, NULL) != 0)
		return (printf("Error: failed to init mutex\n"), EXIT_FAILURE);//
	philo->super->time_last_eaten = (t_time){.tv_sec = 0, .tv_usec = 0};
	philo->super->eating = false;
	philo->super->alive = false;
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
		if (make_philo(table, params, index) == EXIT_FAILURE)
			return (free(*table), EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}
