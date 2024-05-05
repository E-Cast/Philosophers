/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/05 13:18:56 by ecastong         ###   ########.fr       */
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

// int	init_philosophers(t_philo *p, int count)
// {
// 	int	index;

// 	p = malloc((count + 1) * sizeof(t_philo));
// 	if (p == NULL)
// 		return (EXIT_FAILURE);
// 	memset(p, 0, count + 1);
// 	index = 0;
// 	while (index < count)
// 	{
// 		p->id = index + 1;
// 		p->state = EATING;
// 		// pthread_create(&p[index].thread, NULL, &routine, (void *) arg);
// 		index++;
// 	}
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	t_table		table;

	table.start_routine = false;
	if (set_params(&table.params, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_table(&table, table.params) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (verify_arg_count(argc) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	// if (set_table(argc, argv, &table) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
}
