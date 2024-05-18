/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:02 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/18 01:22:13 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	LOG_MSG
		if (stop == true):
			return.
		get current time.
		print message.

	PHILO
		init:
			launch supervisor thread.
			get current time.
			update time_last_eaten for SUPER.
			update time_last_eaten for MONITOR.
			...
		dine:
			while (alive):
				think:
					if (dead):
						break.
					get current_time.
					LOG_MSG.
					lock can_eat mutex.
				eat:
					if (dead):
						break.
					lock fork 1.
					lock fork 2.
					get current_time.
					update time_last_eaten for SUPER.
					update time_last_eaten for MONITOR.
					LOG_MSG.
					sleep for EAT_TIME.
				sleep:
					if (dead):
						break.
					get current_time.
					LOG_MSG.
					sleep for SLEEP_TIME.
			return.

	SUPER
		while (true):
			monitor
			get time_last_eaten.
			get current_time.
			if (current_time - time_last_eaten >= time_to_starve):
				LOG_MSG.
				set philo as dead.
				set program to stop.
				return.
			else if (program set to stop):
				set philo as dead.
				return.

	MONITOR
		while (true)
			if (stop == true):
				unlock all can_eat mutexes.
				return.
			get time_last_eaten for every philo
			find which philo to make eat:
				...
			unlock can_eat mutexes for relevant philos
			...
			wait for fraction of EAT_TIME (one half or one fourth)
			if (stop == true):
				unlock all can_eat mutexes.
				return.
			lock every can_eat mutexes
		
1) find out which philo to make eat and unlock their eat mutexes
2) wait for half the eating time
3) attempt to lock the eat mutexes again
4) loop
meanwhile for the philo
1) think (try to lock the eat mutex)
2) eat (lock the forks, update time last eaten, sleep for eat time, unlock forks and eat mutex)
3) sleep (sleep for sleep time)
4) loop
*/

// int	thread_create(pthread_t *t, void *n, void *routine(void *), void *arg)
// {
// 	return (1);
// 	(void) t;
// 	(void) n;
// 	(void) routine;
// 	(void) arg;
// }

//time.tv_usec / 1000 + 1000 * time.tv_sec

void	log_msg(pthread_mutex_t *lock, bool *stop, int id, char *msg)
{
	t_time	time;

	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	else
		pthread_mutex_unlock(lock);
	gettimeofday(&time, NULL);
	printf("%li %i %s\n", time.tv_usec / 1000 + 1000 * time.tv_sec, id, msg);
}

int	launch_philos(t_table *table, t_params params)
{
	int	index;

	index = 0;
	pthread_mutex_lock(&table->start_lock);
	while (index < params.philo_count)
	{
		if (pthread_create(&table->philo[index].ph_thread, NULL,
				philo, &table->philo[index]) != 0)
		{
			printf("Error: failed to create philo\n");
			pthread_mutex_lock(&table->stop_lock);
			table->stop = true;
			pthread_mutex_unlock(&table->stop_lock);
			break ;
		}
		usleep(1);
		pthread_mutex_lock(&table->philo[index].mp_lock);
		pthread_mutex_unlock(&table->philo[index].mp_lock);
		index++;
	}
	return (index);
}

void	monitor(t_table *table, t_params params)
{
	int	index;

	index = 0;
	while (index < params.philo_count)
		pthread_mutex_lock(&table->can_eat[index++]);
	pthread_mutex_unlock(&table->start_lock);
	(void) params;
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_table		*table;
	int			t_launched;
	int			index;

	if (set_params(&params, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	table = make_table(params);
	if (!table)
		return (printf("Error: failed to make table\n"), EXIT_FAILURE);

	t_launched = launch_philos(table, params);
	if (t_launched == params.philo_count)
		monitor(table, params);
	else
		pthread_mutex_unlock(&table->start_lock);

	index = 0;
	while (index < t_launched)
		pthread_join(table->philo[index++].ph_thread, NULL);
	return (free(table->forks), free(table->can_eat), free(table->philo),
		free(table), EXIT_SUCCESS);
}
