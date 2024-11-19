/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:26:10 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 12:53:40 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_list(t_node **list)
{
	t_node	*current_node;
	int		index; //

	if (list == NULL || *list == NULL)//
		return (-1);
	index = 0; //
	while (*list)
	{
		index++; //
		current_node = *list;
		*list = (*list)->next;
		free(current_node);
	}
	free(*list);
	*list = NULL;
	printf("\n%i\n\n", index);
	return (0);
}

int	new_node(t_node **list, long time, int id, t_msg_id msg)
{
	t_node	*node;
	t_node	*cursor;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (-1);
	node->timestamp = time;
	node->id = id;
	node->msg = msg;
	if (*list == NULL)
		return (*list = node, 0);
	cursor = *list;
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = node;
	return (0);
}
