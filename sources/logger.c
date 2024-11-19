/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:35:16 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 09:31:20 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_end(int t_to_eat, int *t_eaten, t_msg_id msg, int id)
{
	int	index;

	index = 0;
	if (msg == ID_DIE)
		return (-1);
	if (t_to_eat == 0)
		return (0);
	if (msg != ID_EAT)
		return (0);
	t_eaten[id - 1]++;
	index = 0;
	while (t_eaten[index] >= 0)
	{
		if (t_eaten[index] < t_to_eat)
			return (0);
		index++;
	}
	return (-1);
}

static const char	*id_to_msg(t_msg_id id)
{
	if (id == ID_FORK)
		return (MSG_FORK);
	else if (id == ID_EAT)
		return (MSG_EAT);
	else if (id == ID_SLEEP)
		return (MSG_SLEEP);
	else if (id == ID_THINK)
		return (MSG_THINK);
	else
		return (MSG_DIE);
}

static int	logger_loop(t_data *data, int times_to_eat, int *times_eaten)
{
	t_node	*node;

	while (1)
	{
		safe_mutex(&data->mic_lock, pthread_mutex_lock);
		if (*(data->backlog) == NULL)
		{
			safe_mutex(&data->mic_lock, pthread_mutex_unlock);
			usleep(100);
			continue ;//this could possibly become an infinite loop
		}
		node = *(data->backlog);
		*(data->backlog) = (*(data->backlog))->next;
		safe_mutex(&data->mic_lock, pthread_mutex_unlock);
		printf("%li %i %s\n", node->timestamp, node->id, id_to_msg(node->msg));
		if (check_if_end(times_to_eat, times_eaten, node->msg, node->id) != 0)
		{
			safe_mutex(&data->mic_lock, pthread_mutex_lock);
			data->mic_state = STOPPED;
			safe_mutex(&data->mic_lock, pthread_mutex_unlock);
			return (free(node), -1);
		}
		free(node);
	}
}

// make it free the messages as it goes
// optimize
// test for leaks and races

void	*start_logger(void *arg)
{
	t_data		*data;
	int			times_eaten[201];
	int			index;

	data = (t_data *)arg;
	index = 0;
	while (index < data->params.philo_count)
		times_eaten[index++] = 0;
	times_eaten[index] = -1;
	logger_loop(data, data->params.times_to_eat, times_eaten);
	return (NULL);
}
