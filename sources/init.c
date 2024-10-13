/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:05 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/13 10:12:48 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sets every pointer in the data struct to NULL so as to avoid
 * 	calling free on unalocated memory.
 * 
 * @param data Struct to be zeroed.
 */
static void	zero_data(t_data *data)
{
	data->philos = NULL;
	data->threads = NULL;
	data->forks = NULL;
}

/**
 * @brief Frees the t_data struct's allocated members and sets them to NULL.
 * 
 * @param data Struct with the members to free.
 */
void	free_data(t_data *data)
{
	free(data->philos);
	data->philos = NULL;
	free(data->threads);
	data->threads = NULL;
	free(data->forks);
	data->forks = NULL;
}

/**
 * @brief Allocates a struct of mutexes and initializes all of them.
 * 
 * @param n Number of mutexes to put inside the array.
 * @param arr Array to initialize.
 * @retval SUCCESS on success.
 * @retval ERROR on failure.
 */
static int	init_mutex_arr(size_t n, t_mutex **arr)
{
	size_t	index;
	t_mutex	*tmp_arr;

	tmp_arr = ft_calloc(n + 1, sizeof(t_mutex *));
	if (tmp_arr == NULL)
		return (ERROR);
	index = 0;
	while (index < n)
	{
		if (pthread_mutex_init(&tmp_arr[index], NULL) != 0)
			return (free(tmp_arr), tmp_arr = NULL, ERROR);
		index++;
	}
	*arr = tmp_arr;
	return (SUCCESS);
}

/**
 * @brief Allocates and initializes the data struct and it's members.
 * 
 * @param params Struct containing the parameters used in the initialization.
 * @param data Struct to initialize.
 * @retval SUCCESS on success.
 * @retval ERROR on failure.
 */
int	init_data(t_params params, t_data *data)
{
	size_t	n;

	n = params.philo_count;
	zero_data(data);
	data->philos = ft_calloc(n + 1, sizeof(t_philo));
	if (data->philos == NULL)
		return (ERROR);
	data->threads = ft_calloc(n + 1, sizeof(pthread_t));
	if (data->threads == NULL)
		return (free_data(data), ERROR);
	if (init_mutex_arr(n, &data->forks) == ERROR)
		return (free_data(data), ERROR);
	return (SUCCESS);
}
