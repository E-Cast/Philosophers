/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/06 11:13:32 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//set parameters
	//set default parameters
		//number of philosophers
		//time to die
		//time to eat
		//time to sleep
		//optional, number of times each must eat before stopping
	//take input and process it
		//Ensure validity of input
	//set final parameters
		//overwrite default parameters with user input as needed
		//number of forks (number of philos + 1)
		//...
//initialize
	//...
//run
	//...
//terminate
	//...

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

int	launch_threads(t_table *table, t_params params)
{
	unsigned int	i;

	i = 0;
	while (i < params.philo_count)
	{
		pthread_create(&table->threads[i], NULL, &routine, (void *)&table->philos[i]);
		usleep(100);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_table		table;

	if (set_params(&params, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_table(&table, params) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	launch_threads(&table, params);
	usleep(UINT32_MAX);
	return (EXIT_SUCCESS);
}
