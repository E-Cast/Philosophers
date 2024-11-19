/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:35:16 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 06:34:52 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Compares the ascii values of str1 and str2. Returns an
	integer greater than, equal to, or less than 0 depending on 
	if str1 is greater than, equal to, or less than str2*/
static int	my_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	if (!str1 && !str2)
		return (0);
	if (!str1)
		return (-1);
	if (!str2)
		return (1);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

static int	check_if_end(int times_to_eat, int *times_eaten, t_node *node)
{
	int	index;

	index = 0;
	if (my_strcmp(MSG_DIE, node->message) == 0)
		return (-1);
	if (times_to_eat == 0)
		return (0);
	if (my_strcmp(MSG_EAT, node->message) != 0)
		return (0);
	times_eaten[node->id - 1]++;
	index = 0;
	while (times_eaten[index] >= 0)
	{
		if (times_eaten[index] < times_to_eat)
			return (0);
		index++;
	}
	return (-1);
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
		printf("%li %i %s\n", node->timestamp, node->id, node->message);
		if (check_if_end(times_to_eat, times_eaten, node) != 0)
			return (free(node), -1);
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

