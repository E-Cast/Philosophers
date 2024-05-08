/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:04:08 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/06 11:14:45 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_params params, t_table *table)
{
	unsigned int	i;
	t_philo			philo;

	i = 0;
	while (i < params.philo_count)
	{
		philo.l_fork = &table->forks[i];
		philo.r_fork = NULL;
		if (params.philo_count > 1 && i + 1 == params.philo_count)
			philo.r_fork = &table->forks[0];
		else if (params.philo_count > 1)
			philo.r_fork = &table->forks[i + 1];
		philo.thread = &table->threads[i];
		philo.id = i + 1;
		philo.state = EATING;
		philo.times_eaten = 0;
		philo.time_last_eaten = 0;
		philo.params = params;
		table->philos[i] = philo;
		i++;
	}
}

int	init_forks(t_table *table, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			printf("Error\n");//
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_table(t_table *table, t_params params)
{
	table->philos = ph_calloc(params.philo_count + 1, sizeof(t_philo));
	if (table->philos == NULL)
		return (EXIT_FAILURE);
	table->forks = ph_calloc(params.philo_count + 1, sizeof(pthread_mutex_t));
	if (table->forks == NULL)
		return (free(table->philos), EXIT_FAILURE);
	table->threads = ph_calloc(params.philo_count + 1, sizeof(pthread_t));
	if (table->threads == NULL)
		return (free(table->philos), free(table->forks), EXIT_FAILURE);
	init_philos(params, table);
	init_forks(table, params.philo_count);
	return (EXIT_SUCCESS);
}
