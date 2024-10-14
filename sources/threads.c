/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:55:55 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/14 14:40:03 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(int n, pthread_t *threads)
{
	int	index;

	index = 0;
	while (index < n)
	{
		pthread_join(threads[index], NULL);
		index++;
	}
}

int	launch_threads(int n, t_data data)
{
	int	index;

	index = 0;
	while (index < n)
	{
		if (pthread_create(&data.threads[index], NULL,
				start_routine, &data.philos[index]))
			return (printf("test\n"), ERROR);
		usleep(10);
		index++;
	}
	return (SUCCESS);
}
