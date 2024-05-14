/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:09 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/14 15:23:40 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, suseconds_t time, char *action)
{
	pthread_mutex_lock(philo->super.stop_lock);
	if (*philo->stop == true)
		return ;
	pthread_mutex_unlock(philo->super.stop_lock);
	printf("%li %i %s\n", time, philo->id, action);
}

void	eat(t_philo *philo)
{
	t_time	time;

	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(&philo->lock);
	gettimeofday(&time, NULL);
	philo->super.time_last_eaten = time;
	pthread_mutex_unlock(&philo->lock);
	print_action(philo, time.tv_usec, "is eating");
	usleep(philo->params.time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	gettimeofday(&time, NULL);
	print_action(philo, time.tv_usec, "is sleeping");
	usleep(philo->params.time_to_sleep);
	gettimeofday(&time, NULL);
	print_action(philo, time.tv_usec, "is thinking");
}

void	dine(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->super.lock);
		if (philo->super.alive == false)
		{
			pthread_mutex_unlock(&philo->super.lock);
			return ;
		}
		pthread_mutex_unlock(&philo->super.lock);
		pthread_mutex_lock(&philo->lock);
		if (philo->can_eat == true)
		{
			philo->can_eat = false;
			philo->eating = true;
			pthread_mutex_unlock(&philo->lock);
			eat(philo);
		}
		else
			pthread_mutex_unlock(&philo->lock);
	}
	return ;
}

void	*philo_start(void *arg)
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
		print_action(philo, time.tv_usec, "is thinking");
		if (pthread_create(&thread, NULL, supervisor, &philo->super) != 0)
			return (printf("Error: failed to create thread\n"), NULL);//
		dine(philo);
		pthread_join(thread, NULL);
	}
	return (NULL);
}
