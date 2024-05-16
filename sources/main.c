/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:02 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/16 19:13:46 by ecastong         ###   ########.fr       */
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
			else if (program set to stop):
				set philo as dead.


		
1) find out which philo to make eat and unlock their eat mutexes
2) wait for half the eating time
3) attempt to lock the eat mutexes again
4) loop
meanwhile for the philo
1) think (try to lock the eat mutex)
2) eat (lock the forks, update time last eaten, sleep for eat time, unlock forks and eat mutex)
3) sleep (sleep for sleep time)
4) loop
	MONITOR
		get time last eaten for all
		unlock eat mutexes for the ones that need it the most
		How and when do I re lock the mutexes?
*/

void	log_msg(pthread_mutex_t *lock, bool *stop, int id, char msg)
{
	t_time	time;

	pthread_mutex_lock(lock);
	if (*stop == true)
		return (pthread_mutex_unlock(lock), (void) 0);
	pthread_mutex_unlock(lock);
	gettimeofday(&time, NULL);
	printf("%li %i %i\n", time, id, msg);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (set_params(&params, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//alloc and init the structs and mutexes
	//launch threads
	return (EXIT_SUCCESS);
}
