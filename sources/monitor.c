/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:32:50 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 10:32:26 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks to see if a philo has starved by comparing the 
 * time it last ate to the current time.
 * 
 * @param philo Philosophers to check.
 * @param time_to_die Time a philosopher can go without eating before starving.
 * @retval 0 if the philo has not starved.
 * @retval -1 if the philo has died.
 */
static int	starvation_check(t_philo *philo, int time_to_die)
{
	long	time;

	time = gettime_ms();
	if (time - philo->time_last_eaten < time_to_die)
		return (0);
	safe_mutex(philo->mic_lock, pthread_mutex_lock);
	*philo->mic_status = STOP;
	if (0 > printf("%li %i %s\n", time, philo->id, "died"))
		write(1, "Error: printf failed.", 22);
	safe_mutex(philo->mic_lock, pthread_mutex_unlock);
	philo->status = STOP;
	return (-1);
}

int	monitor_cycle(t_data *data, t_params params)
{
	int		index;
	t_philo	*philo;

	index = 0;
	while (index < params.philo_count)
	{
		philo = &data->philos[index];
		safe_mutex(philo->info_lock, pthread_mutex_lock);
		if (starvation_check(philo, params.time_to_die) == -1)
			return (safe_mutex(philo->info_lock, pthread_mutex_unlock), -1);
		// check if sated
		safe_mutex(philo->info_lock, pthread_mutex_unlock);
		index++;
	}
	return (1);
}

void	stop_all(t_data *data, int philo_count)
{
	int		index;

	index = 0;
	while (index < philo_count)
	{
		data->philos[index].status = STOP;
		index++;
	}
	return ;
}

void	*start_monitor(void *arg)//tmp
{
	t_data	*data;

	data = (t_data *)arg;
	while (monitor_cycle(data, data->params) == 1)
		(void) data;
	stop_all(data, data->params.philo_count);
	return (NULL);
}
