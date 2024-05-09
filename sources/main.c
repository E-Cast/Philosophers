/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/09 14:06:48 by ecastong         ###   ########.fr       */
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

void	*routine(void *param)
{
	t_philo	*p;
	t_state	state;
	t_time	time_last_eaten;
	t_time	time;
	int		times_eaten;

	p = (t_philo *)param;
	state = THINKING;
	gettimeofday(&time_last_eaten, NULL);
	printf("%i %i is thinking\n", time_last_eaten.tv_usec, p->id);
	times_eaten = 0;
	while (p->dead == false)
	{
		if (state != THINKING)
		{
			state = THINKING;
			gettimeofday(&time, NULL);
			printf("%i %i is thinking\n", time.tv_usec, p->id);
		}
		if (state == THINKING && *(p->can_eat) == true && p->fork_l)
		{
			pthread_mutex_lock(p->fork_l);
			gettimeofday(&time, NULL);
			printf("%i %i has taken a fork\n", time.tv_usec, p->id);
			pthread_mutex_lock(p->fork_r);
			gettimeofday(&time, NULL);
			printf("%i %i has taken a fork\n", time.tv_usec, p->id);
			gettimeofday(&time, NULL);//
			printf("%i %i is eating\n", time.tv_usec, p->id);
			state = EATING;
			time_last_eaten = time;
			times_eaten++;
			usleep(p->params.time_to_eat);
			gettimeofday(&time, NULL);//
			printf("%i %i is sleeping\n", time.tv_usec, p->id);
			usleep(p->params.time_to_sleep);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_table		table;

	if (set_params(&params, argc, argv) != 0)
		return (EXIT_FAILURE);
	if (set_table(&table, params) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
