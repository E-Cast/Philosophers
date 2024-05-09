/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:45:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/09 14:16:08 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, count * size);
	return ((void *)ptr);
}

int	init_table(t_table *table, int size)
{
	table->forks = ft_calloc(size, sizeof(pthread_mutex_t));
	table->philos = ft_calloc(size, sizeof(t_philo));
	table->can_eat = ft_calloc(size, sizeof(bool));
	table->dead = ft_calloc(size, sizeof(bool));
	table->threads = ft_calloc(size, sizeof(pthread_t));
	if (!table->forks || !table->philos || !table->threads)
	{
		if (table->forks)
			free(table->forks);
		if (table->philos)
			free(table->philos);
		if (table->can_eat)
			free(table->can_eat);
		if (table->dead)
			free(table->dead);
		if (table->threads)
			free(table->threads);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_philo	make_philo(t_table *table, t_params params, int index)
{
	t_philo	p;

	p.id = index + 1;
	p.can_eat = &table->can_eat[index];
	p.dead = &table->dead[index];
	p.fork_r = &table->forks[index];
	if (params.philo_count == 1)
		p.fork_l = NULL;
	else if (index + 1 == params.philo_count)
		p.fork_l = &table->forks[0];
	else
		p.fork_l = &table->forks[index + 1];
	return (p);
}

int	set_table(t_table *table, t_params params)
{
	int	index;

	if (init_table(table, params.philo_count + 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	index = 0;
	while (index < params.philo_count)
	{
		pthread_mutex_init(&table->forks[index], NULL);
		table->philos[index] = make_philo(table, params, index);
		pthread_create(&table->threads[index], NULL, routine,
			(void *)&table->philos[index]);//
		usleep(1);
		index++;
	}
	return (EXIT_SUCCESS);
}
