/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:51:49 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/07 10:53:03 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *)param;
	gettimeofday(&time, NULL);
	philo->time_last_eaten = time.tv_usec;
	// usleep(600000);
	// printf("%i done\n", philo->id);
	while (philo->state != DEAD)
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec - philo->time_last_eaten >= philo->params.time_to_die)
		{
			philo->state = DEAD;
			break ;
		}
	}
	if (philo->state == DEAD)
	{
		gettimeofday(&time, NULL);
		printf("%i %i died\n", time.tv_usec, philo->id);
	}
	return (NULL);
}
