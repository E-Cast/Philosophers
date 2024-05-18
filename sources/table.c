/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 01:47:49 by ecastong         ###   ########.fr       */
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
		return (printf("Error: allocation failed\n"), NULL);
	memset(ptr, 0, count * size);
	return ((void *)ptr);
}

int	make_super(t_philo *philo)
{
	t_super	super;

	super.params = philo->params;
	super.id = philo->id;
	super.stop_lock = philo->stop_lock;
	super.stop = philo->stop;

	if (pthread_mutex_init(&super.sp_lock, NULL) != 0)
		return (printf("Error: failed to make supervisor\n"), EXIT_FAILURE);
	super.sp_alive = true;
	// super.sp_t_last_ate = (t_time){.tv_sec = 0, .tv_usec = 0};

	philo->super = super;
	return (EXIT_SUCCESS);
}

int	make_philo(t_table *table, t_params params, int index)
{
	t_philo	philo;

	philo.params = params;
	philo.id = index + 1;
	philo.start_lock = &table->start_lock;
	philo.stop_lock = &table->stop_lock;
	philo.stop = &table->stop;
	philo.can_eat = &table->can_eat[index];
	philo.fork_r = &table->forks[index];
	if (params.philo_count == 1)
		philo.fork_l = NULL;
	else if (index + 1 == params.philo_count)
		philo.fork_l = &table->forks[0];
	else
		philo.fork_l = &table->forks[index + 1];

	if (pthread_mutex_init(&philo.mp_lock, NULL) != 0)
		return (printf("Error: failed to make philo\n"), EXIT_FAILURE);
	// philo.mp_alive = true;
	// philo.mp_t_last_ate.tv = (struct timeval){.tv_sec = 0, .tv_usec = 0};
	if (make_super(&philo) == EXIT_FAILURE)
		return (printf("Error: failed to make philo\n"), EXIT_FAILURE);

	table->philo[index] = philo;
	return (EXIT_SUCCESS);
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
				free(table->philo), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_table	*make_table(t_params params)
{
	t_table	*table;

	table = ph_calloc(1, sizeof(t_table));
	if (!table)
		return (NULL);
	if (pthread_mutex_init(&table->start_lock, NULL) != 0)
		return (free(table), printf("Error: failed to alloc table\n"), NULL);
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		return (free(table), printf("Error: failed to alloc table\n"), NULL);
	table->stop = false;
	if (make_arrays(table, params) == EXIT_FAILURE)
		return (free(table), printf("Error: failed to make arrays\n"), NULL);
	return (table);
}
