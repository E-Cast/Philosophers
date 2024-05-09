/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:45:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/08 09:58:14 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return ((void *)ptr);
}

void	safer_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

int	init_table(t_table *table, int size)
{
	table->forks = ft_calloc(size, sizeof(pthread_mutex_t));
	table->philos = ft_calloc(size, sizeof(t_philo));
	table->info_lock = ft_calloc(size, sizeof(pthread_mutex_t));
	table->can_eat = ft_calloc(size, sizeof(bool));
	table->dead = ft_calloc(size, sizeof(bool));
	table->threads = ft_calloc(size, sizeof(pthread_t));
	if (!table->forks || !table->philos || !table->info_lock
		|| !table->can_eat || !table->dead || !table->threads)
	{
		safer_free(table->forks);
		safer_free(table->philos);
		safer_free(table->info_lock);
		safer_free(table->can_eat);
		safer_free(table->dead);
		safer_free(table->threads);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// typedef struct s_philosopher
// {
// 	t_params		params;

// 	int				id;
// 	t_state			state;
// 	t_time			time_last_eaten;
// 	int				times_eaten;

// 	pthread_mutex_t	*fork_l;
// 	pthread_mutex_t	*fork_r;
// 	pthread_mutex_t	*info_lock;
// 	bool			*can_eat;
// 	bool			*dead;
// }	t_philo;
t_philo	make_philo(t_table *table, int index)
{
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
		pthread_mutex_init(&table->info_lock[index], NULL);
		table->can_eat[index] = false;
		table->dead[index] = false;
		table->philos[index] = make_philo(table, index);
		index++;
	}
	// index = 0;
	// while (index < params.philo_count)
	// {
	// 	table->philos[index] = make_philo(table.);
	// }
	return (EXIT_FAILURE);
}
