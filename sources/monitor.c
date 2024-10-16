/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:32:50 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 10:16:05 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo, t_params params)
{
	long	time;

	time = gettime_ms();
	if (time - philo->time_last_eaten >= params.time_to_die)
	{
		log_msg(time, philo, MSG_DIE);
		printf("\n");
		philo->status = STOP;
		return (-1);
	}
	return (1);
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
		if (check_dead(philo, params) == -1)
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
