/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:04:08 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/05 13:59:42 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(unsigned int philo_count, t_table *table)
{
	unsigned int	i;
	t_philo			philo;

	i = 0;
	while (i < philo_count)
	{
		philo.l_fork = &table->forks[i];
		philo.r_fork = NULL;
		if (philo_count > 1 && i + 1 == philo_count)
			philo.r_fork = &table->forks[0];
		else if (philo_count > 1)
			philo.r_fork = &table->forks[i + 1];
		philo.thread = &table->threads[i];
		philo.id = i + 1;
		philo.state = EATING;
		philo.times_eaten = 0;
		philo.time_last_eaten = 0;
		table->philos[i] = philo;
		i++;
	}
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
	init_philos(params.philo_count, table);
	//init_forks
	//if fail return fail
	//init_threads
	//if fail return fail
	return (EXIT_SUCCESS);
}
