/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/16 20:21:03 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*h_calloc(size_t count, size_t size)
// {
// 	return (NULL);
// 	(void) count;
// 	(void) size;
// }

// int	thread_mutex_init(pthread_mutex_t *m, pthread_mutexattr_t *a)
// {
// 	return (1);
// 	(void) m;
// 	(void) a;
// }

void	*ph_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, count * size);
	return ((void *)ptr);
}

int	make_arrays(t_table *table, t_params params)
{
	int	index;

	table->forks = ph_calloc(params.philo_count + 1, sizeof(pthread_mutex_t));
	if (!table->forks)
		return (EXIT_FAILURE);
	table->can_eat = ph_calloc(params.philo_count + 1, sizeof(pthread_mutex_t));
	if (!table->can_eat)
		return (free(table->forks), EXIT_FAILURE);
	table->philo = ph_calloc(params.philo_count + 1, sizeof(t_philo));
	if (!table->philo)
		return (free(table->forks), free(table->can_eat), EXIT_FAILURE);
	index = -1;
	while (index++ < params.philo_count - 1)
	{
		if (pthread_mutex_init(&table->forks[index], NULL) != 0)
			return (free(table->forks), free(table->can_eat),
				free(table->philo), EXIT_FAILURE);
		if (pthread_mutex_init(&table->can_eat[index], NULL) != 0)
			return (free(table->forks), free(table->can_eat),
				free(table->philo), EXIT_FAILURE);
		if (make_philo(table, params, index) == EXIT_FAILURE)
			return (free(table->forks), free(table->can_eat),
				free(table->philo), EXIT_FAILURE);//
	}
	return (EXIT_SUCCESS);
}

t_table	*make_table(t_params params)
{
	t_table	*table;

	table = ph_calloc(1, sizeof(t_table));
	if (!table)
		return (printf("Error: failed to make table\n"), NULL);
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		return (free(table), printf("Error: failed to make table\n"), NULL);
	table->stop = false;
	if (make_arrays(table, params) == EXIT_FAILURE)
		return (free(table), printf("Error: failed to make arrays\n"), NULL);//
	return (table);
}
