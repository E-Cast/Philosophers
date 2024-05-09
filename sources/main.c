/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/08 09:45:37 by ecastong         ###   ########.fr       */
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


// typedef struct s_table
// {
// 	int				*times_eaten;

// 	pthread_mutex_t	*forks;
// 	t_philo			*philos;
// 	pthread_mutex_t	*info_lock;
// 	bool			*can_eat;
// 	bool			*dead;
// 	pthread_t		*threads;
// }	t_table;

int	main(int argc, char **argv)
{
	t_params	params;
	t_table		table;

	if (set_params(&params, argc, argv) != 0)
		return (EXIT_FAILURE);
	if (set_table(&table, params) == EXIT_FAILURE);
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
