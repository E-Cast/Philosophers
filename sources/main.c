/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:21:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/11 14:29:59 by ecastong         ###   ########.fr       */
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

// void	*monitor(void *args)
// {
// 	t_params	params;
// 	t_table		*table;
// 	int			index;

// 	params = ((t_monitor *)args)->params;
// 	table = ((t_monitor *)args)->table;
// 	printf("philo_count:%i\n", params.philo_count);
// 	while (true)
// 	{
// 		index = 0;
// 	}
// 	(void) index;
// 	(void) table;
// 	(void) params;
// }

// int	thread_create(pthread_t *t, pthread_attr_t *t_a, void *(* routine)(void *), void *arg)
// {
// 	(void) t;
// 	(void) t_a;
// 	(void) routine;
// 	(void) arg;
// 	return (1);
// }

// pthread_mutex_lock(&super->lock);
// pthread_mutex_unlock(&super->lock);
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
		// pthread_mutex_unlock(&super->lock);
		gettimeofday(&time, NULL);
		if (time.tv_usec - time_last_eaten.tv_usec >= super->params.time_to_die)
		{
			printf("%li %i died\n", time.tv_usec, super->id);
			// pthread_mutex_lock(&super->lock);
			super->alive = false;
			// pthread_mutex_unlock(&super->lock);
			break ;
		}
		pthread_mutex_unlock(&super->lock);//
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
	pthread_mutex_lock(&philo->super->lock);
	gettimeofday(&time, NULL);
	*philo.time_last_eaten = time;
	pthread_mutex_unlock(&philo->super->lock);
	printf("%li %i is thinking\n", time.tv_usec, philo.id);
	if (pthread_create(&thread, NULL, supervisor, philo.super) != 0)//
		return (NULL);
	alive = true;//
	while (true)
	{
		gettimeofday(&time, NULL);
		// alive = *philo.alive;
		pthread_mutex_unlock(&philo.sup_lock);
		if (alive == false)
			break ;
	}
	pthread_join(thread, NULL);
	return (arg);
}

void	*start_philos(void *arg)
{
	t_table		*table;
	t_params	params;
	int			index;
	int			jndex;

	table = (t_table *)arg;
	params = table[0].philo->params;
	index = 0;
	while (index < params.philo_count)
	{
		usleep(1);//
		if (pthread_create(&table[index].thread, NULL, dine,
			(void *)&table[index].philo) != 0)//
			break ;
		index++;
	}
	jndex = 0;
	while (jndex < index)
		pthread_join(table[jndex++].thread, NULL);
	return (table);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_table		*table;
	pthread_t	thread;

	if (set_params(&params, argc, argv) != 0)
		return (EXIT_FAILURE);
	if (init_table(&table, params) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_create(&thread, NULL, start_philos, (void *)table) != 0)
		return (free(table), printf("Error: failed to create thread\n"),
			EXIT_FAILURE);
	//coordinate threads
	//there should be no threads running by the time coordiate returns;
	pthread_join(thread, NULL);
	free(table);
	return (EXIT_SUCCESS);
}
