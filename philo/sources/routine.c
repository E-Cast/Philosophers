/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:51:49 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/07 11:21:34 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_states	get_state(t_philo	*philo)
{
	t_states	state;

	pthread_mutex_lock(&philo->state);
	state = philo->state;
	pthread_mutex_unlock(&philo->state);
	return (state);
}

void	eat(t_philo *philo, unsigned int time_to_eat)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->l_fork);
	gettimeofday(&time, NULL);
	printf("%i %i has taken a fork\n", time.tv_usec, philo->id);
	pthread_mutex_lock(&philo->r_fork);
	gettimeofday(&time, NULL);
	printf("%i %i has taken a fork\n", time.tv_usec, philo->id);
	pthread_mutex_lock(&philo->time_last_eaten);
	gettimeofday(&time, NULL);
	printf("%i %i is eating\n", time.tv_usec, philo->id);
	philo->time_last_eaten = time.tv_usec;
	pthread_mutex_unlock(&philo->time_last_eaten);
	usleep(time_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	return ;
}

void	sleep(t_philo *philo, unsigned int time_to_sleep)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->state);
	gettimeofday(&time, NULL);
	printf("%i %i is sleeping\n", time.tv_usec, philo->id);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state);
	usleep(time_to_sleep);
	return ;
}

void	think(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->state);
	gettimeofday(&time, NULL);
	printf("%i %i is thinking\n", time.tv_usec, philo->id);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->state);
	return ;
}

void	*routine(void *arg)
{
	t_params	params;
	t_states	state;

	params = ((t_philo *)arg)->params;
	state = EATING;
	while (state != DEAD)
	{
		state = get_state((t_philo *)arg);
		if (state == DEAD)
			return (NULL);
		if (state == EATING)
		{
			eat((t_philo *)arg, params.time_to_eat);
			sleep((t_philo *)arg, params.time_to_sleep);
			think((t_philo *)arg);
		}
	}
}

// void	*routine(void *param)
// {
// 	t_philo			*philo;
// 	struct timeval	time;

// 	philo = (t_philo *)param;
// 	gettimeofday(&time, NULL);
// 	philo->time_last_eaten = time.tv_usec;
// 	// usleep(600000);
// 	// printf("%i done\n", philo->id);
// 	while (philo->state != DEAD)
// 	{
// 		gettimeofday(&time, NULL);
// 		if (time.tv_usec - philo->time_last_eaten >= philo->params.time_to_die)
// 		{
// 			philo->state = DEAD;
// 			break ;
// 		}
// 	}
// 	if (philo->state == DEAD)
// 	{
// 		gettimeofday(&time, NULL);
// 		printf("%i %i died\n", time.tv_usec, philo->id);
// 	}
// 	return (NULL);
// }
