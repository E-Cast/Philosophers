/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:42:41 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/07 12:43:47 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	waiter(t_table *table, t_params params)
{
	bool	no_deaths;
	int		index;

	no_deaths = true;
	while (no_deaths == true)
	{
		no_deaths = check_for_deaths();
		if (philos_not_done_eating() == 0)
			return (EXIT_SUCCESS);
		index = hungriest_philosopher();
		if (philo(index - 1) != EATING && philo(index + 1) != EATING)
		{
			set_philo_state(index, EATING);
			set_time_last_eaten(index);
			times_eaten++;
		}
	}
	return (EXIT_SUCCESS);
}
