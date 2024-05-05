/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/05 12:01:51 by ecastong         ###   ########.fr       */
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

// //storing the number of philo might not be needed
// int	set_table(int argc, char **argv, t_table *table)
// {
// 	int	tmp;

// 	tmp = ph_atoui(argv[1]);
// 	if (init_philosophers(table->philos, tmp) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	table->time_to_die = ph_atoui(argv[2]);
// 	table->time_to_eat = ph_atoui(argv[3]);
// 	table->time_to_sleep = ph_atoui(argv[4]);
// 	table->time_eaten_to_end = -1;
// 	if (argc == 6)
// 		table->time_eaten_to_end = ph_atoui(argv[5]);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	t_params	params;

	if (set_params(&params, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (verify_arg_count(argc) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	// if (set_table(argc, argv, &table) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
}
