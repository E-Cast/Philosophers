/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/12 23:19:47 by ecastong         ###   ########.fr       */
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

void	*supervisor(void *arg)
{
	t_super		*super;
	t_time		time;
	t_time		time_last_eaten;

	super = (t_super *)arg;
	while (true)
	{
		pthread_mutex_lock(&super->lock);
		time_last_eaten = super->time_last_eaten;
		gettimeofday(&time, NULL);
		if (time.tv_usec - time_last_eaten.tv_usec >= super->params.time_to_die)
		{
			printf("%li %i died\n", time.tv_usec, super->id);
			super->alive = false;
			pthread_mutex_unlock(&super->lock);
			pthread_mutex_lock(super->stop_lock);
			*super->stop = true;
			pthread_mutex_unlock(super->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&super->lock);
		pthread_mutex_lock(super->stop_lock);
		if (*super->stop == true)
		{
			pthread_mutex_unlock(super->stop_lock);
			pthread_mutex_lock(&super->lock);
			super->alive = false;
			pthread_mutex_unlock(&super->lock);
			break ;
		}
		else
			pthread_mutex_unlock(super->stop_lock);
	}
	return (arg);
}

void	*dine(void *arg)
{
	t_philo		*philo;
	t_time		time;
	pthread_t	thread;
	bool		alive;

	philo = (t_philo *)arg;
	alive = true;
	pthread_mutex_lock(philo->super.stop_lock);
	if (*philo->super.stop == true)
		alive = false;
	pthread_mutex_unlock(philo->super.stop_lock);
	if (alive)
	{
		pthread_mutex_lock(&philo->super.lock);
		gettimeofday(&time, NULL);
		philo->super.time_last_eaten = time;
		pthread_mutex_unlock(&philo->super.lock);
		printf("%li %i is thinking\n", time.tv_usec, philo->id);
		if (pthread_create(&thread, NULL, supervisor, &philo->super) != 0)//
			return (NULL);
	}
	// pthread_mutex_lock(&philo->super.lock);
	// gettimeofday(&time, NULL);
	// philo->super.time_last_eaten = time;
	// pthread_mutex_unlock(&philo->super.lock);
	// printf("%li %i is thinking\n", time.tv_usec, philo->id);
	// if (pthread_create(&thread, NULL, supervisor, &philo->super) != 0)//
	// 	return (NULL);
	while (alive)
	{
		pthread_mutex_lock(&philo->super.lock);
		if (philo->super.alive == false)
			alive = false;
		pthread_mutex_unlock(&philo->super.lock);
		if (alive == false)
			break ;
	}
	pthread_join(thread, NULL);
	return (arg);
}

void	*start_philos(void *arg)
{
	t_data	*data;
	int		index;
	int		jndex;

	data = (t_data *)arg;
	index = 0;
	while (index < data->params.philo_count)
	{
		usleep(1);//
		if (pthread_create(&data->table[index].thread, NULL, dine,
				(void *)&data->table[index].philo) != 0)
			break ;
		index++;
	}
	jndex = 0;
	while (jndex < index)
		pthread_join(data->table[jndex++].thread, NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (printf("Error: failed to alloc memory\n"), EXIT_FAILURE);
	if (set_params(&data->params, argc, argv) != 0)
		return (free(data), EXIT_FAILURE);
	if (init_table(data, data->params) == EXIT_FAILURE)
		return (free(data), EXIT_FAILURE);
	if (pthread_create(&data->thread, NULL, start_philos, (void *)data) != 0)
		return (printf("Error: failed to create thread\n"),
			free(data->table), free(data), EXIT_FAILURE);
	//coordinate threads
	//there should be no threads running by the time coordiate returns;
	pthread_join(data->thread, NULL);
	return (free(data->table), free(data), EXIT_SUCCESS);
}
