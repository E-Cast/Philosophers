/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:45:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/10 22:07:33 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

// int	init_table(t_table **t, t_params params)
// {
// 	int		index;
// 	t_table	*table;//temporary measure, change **t back to **table and remove this later

// 	table = malloc((params.philo_count + 1) * sizeof(t_table));
// 	if (!table)
// 		return (printf("Error: failed to alloc memory\n"), EXIT_FAILURE);
// 	memset(table, 0, params.philo_count + 1);
// 	index = 0;
// 	while (index < params.philo_count)
// 	{
// 		pthread_mutex_init(&table[index].fork, NULL);//
// 		pthread_mutex_init(&table[index].lock, NULL);//
// 		table[index].can_eat = false;
// 		table[index].eating = false;
// 		table[index].dead = false;
// 		index++;
// 	}
// 	*t = table;//
// 	return (EXIT_SUCCESS);
// }

// #include "philo.h"

// void	*ft_calloc(size_t count, size_t size)
// {
// 	unsigned char	*ptr;

// 	ptr = malloc(count * size);
// 	if (!ptr)
// 		return (NULL);
// 	memset(ptr, 0, count * size);
// 	return ((void *)ptr);
// }

// int	init_table(t_table *table, int size)
// {
// 	table->forks = ft_calloc(size, sizeof(pthread_mutex_t));
// 	table->philos = ft_calloc(size, sizeof(t_philo));
// 	table->can_eat = ft_calloc(size, sizeof(bool));
// 	table->dead = ft_calloc(size, sizeof(bool));
// 	table->threads = ft_calloc(size, sizeof(pthread_t));
// 	if (!table->forks || !table->philos || !table->threads)
// 	{
// 		if (table->forks)
// 			free(table->forks);
// 		if (table->philos)
// 			free(table->philos);
// 		if (table->can_eat)
// 			free(table->can_eat);
// 		if (table->dead)
// 			free(table->dead);
// 		if (table->threads)
// 			free(table->threads);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

// t_philo	make_philo(t_table *table, t_params params, int index)
// {
// 	t_philo	p;

// 	p.id = index + 1;
// 	p.can_eat = &table->can_eat[index];
// 	p.dead = &table->dead[index];
// 	p.fork_r = &table->forks[index];
// 	if (params.philo_count == 1)
// 		p.fork_l = NULL;
// 	else if (index + 1 == params.philo_count)
// 		p.fork_l = &table->forks[0];
// 	else
// 		p.fork_l = &table->forks[index + 1];
// 	return (p);
// }

// int	set_table(t_table *table, t_params params)
// {
// 	int	index;

// 	if (init_table(table, params.philo_count + 1) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	index = 0;
// 	while (index < params.philo_count)
// 	{
// 		pthread_mutex_init(&table->forks[index], NULL);
// 		table->philos[index] = make_philo(table, params, index);
// 		pthread_create(&table->threads[index], NULL, routine,
// 			(void *)&table->philos[index]);//
// 		usleep(1);
// 		index++;
// 	}
// 	return (EXIT_SUCCESS);
// }
