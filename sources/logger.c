/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:35:16 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 00:51:34 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	log_next_message(t_data *data, t_params params, t_node **backlog)
// {
// 	t_node	*node;

// 	printf("test\n");
// 	node = *backlog;
// 	while (node != NULL)
// 	{
// 		printf("%li %i %s\n", node->timestamp, node->id, node->message);
// 		node = node->next;
// 	}
// 	// safe_mutex(&data->mic_lock, pthread_mutex_lock);
// 	// // if (data->mic_state == STOPPED)
// 	// // 	return (-1);
// 	// if (*backlog == NULL)
// 	// 	return (0);
// 	// node = *backlog;
// 	// *backlog = node->next;
// 	// safe_mutex(&data->mic_lock, pthread_mutex_unlock);
// 	// printf("%li %i %s\n", node->timestamp, node->id, node->message);
// 	// free (node);
// 	(void) params;//
// 	(void) data;
// 	return (0);
// }

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

void	*start_logger(void *arg)
{
	t_data		*data;
	t_node		**backlog;
	t_node		*node;

	data = (t_data *)arg;
	backlog = data->backlog;
	printf ("logger started\n");
	while (1)
	{
		safe_mutex(&data->mic_lock, pthread_mutex_lock);
		node = *backlog;
		if (node == NULL)
		{
			safe_mutex(&data->mic_lock, pthread_mutex_unlock);
			usleep(100);
			continue ;
		}
		*backlog = node->next;
		safe_mutex(&data->mic_lock, pthread_mutex_unlock);
		printf("%li %i %s\n", node->timestamp, node->id, node->message);
		if (my_strcmp(MSG_DIE, node->message) == 0)
			break ;
	}
	return (NULL);
}

