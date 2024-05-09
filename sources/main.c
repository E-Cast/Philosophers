/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/09 19:04:16 by ecastong         ###   ########.fr       */
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

// void	*supervisor(void *param)
// {
// 	t_philo	*p;

// 	p = (t_philo *)param;
// 	while (true)
// 	{
		
// 	}
// }

// void	*routine(void *param)
// {
// 	t_philo	*p;
// 	t_state	state;
// 	t_time	time;
// 	int		times_eaten;

// 	p = (t_philo *)param;
// 	state = THINKING;
// 	gettimeofday(&p->time_last_eaten, NULL);
// 	printf("%li %i is thinking\n", p->time_last_eaten.tv_usec, p->id);
// 	times_eaten = 0;
// 	while (*p->dead == false)
// 	{
// 		if (state != THINKING)
// 		{
// 			state = THINKING;
// 			gettimeofday(&time, NULL);
// 			printf("%li %i is thinking\n", time.tv_usec, p->id);
// 		}
// 		if (*p->dead == false && state == THINKING && *p->can_eat == true && p->fork_l)
// 		{
// 			pthread_mutex_lock(p->fork_l);
// 			gettimeofday(&time, NULL);
// 			printf("%li %i has taken a fork\n", time.tv_usec, p->id);
// 			pthread_mutex_lock(p->fork_r);
// 			gettimeofday(&time, NULL);
// 			printf("%li %i has taken a fork\n", time.tv_usec, p->id);
// 			gettimeofday(&time, NULL);//
// 			printf("%li %i is eating\n", time.tv_usec, p->id);
// 			state = EATING;
// 			p->time_last_eaten = time;
// 			times_eaten++;
// 			usleep(p->params.time_to_eat);
// 		}
// 		if (*p->dead == false && state == EATING)
// 		{
// 			state = SLEEPING;
// 			gettimeofday(&time, NULL);//
// 			printf("%li %i is sleeping\n", time.tv_usec, p->id);
// 			usleep(p->params.time_to_sleep);
// 		}
// 	}
// 	return (NULL);
// }

// void	monitor_deaths(t_table *table, int philo_count, int time_to_die)
// {
// 	int		index;
// 	t_time	time;
// 	t_philo	p;

// 	index = 0;
// 	while (index < philo_count)
// 	{
// 		p = table->philos[index];
// 		gettimeofday(&time, NULL);
// 		if (table->dead[index] == false && p.time_last_eaten.tv_usec - time.tv_usec >= time_to_die)
// 		{
// 			table->dead[index] = true;
// 			printf("%i %i died\n", time.tv_usec, p.id);
// 			printf("index:%i id:%i\n", index, p.id);
// 		}
// 		index++;
// 	}
// }

// int	monitor(t_table *table, t_params params)
// {
// 	int	index;

// 	while (true)
// 	{
// 		monitor_deaths(table, params.philo_count, params.time_to_die);
// 		index = 0;

// 	}
// }

int	main(int argc, char **argv)
{
	t_params	params;
	t_table		*table;

	if (set_params(&params, argc, argv) != 0)
		return (EXIT_FAILURE);
	if (init_table(&table, params) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (table)
		printf("test\n");
	// monitor(&table, params);
	return (EXIT_SUCCESS);
}
