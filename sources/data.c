/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:05 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/13 15:21:31 by ecastong         ###   ########.fr       */
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
	t_mutex	*array;

	array = ft_calloc(n + 1, sizeof(t_mutex));
	if (array == NULL)
		return (printf("Error: allocation failed.\n"), ERROR);
	index = 0;
	while (index < n)
	{
		if (pthread_mutex_init(&array[index], NULL) != 0)
		{
			printf("Error: mutex_init failed.\n");
			return (free(array), ERROR);
		}
		index++;
	}
	return (*arr = array, SUCCESS);
}

/**
 * @brief Initializes a philo struct and returns it.
 * 
 * @param params Program's parameters.
 * @param data Struct holding all the program's allocated variables.
 * @param index Index used to retrieved variables
 * 	from the arrays in the data struct.
 */
static t_philo	init_philo(t_params params, t_data *data, int index)
{
	t_philo	philo;

	philo.id = index + 1;
	philo.parameters = params;
	philo.fork_l = &data->forks[index];
	philo.start_lock = &data->start_lock;
	if (params.philo_count == 1)
		philo.fork_r = NULL;
	else if (index + 1 == params.philo_count)
		philo.fork_r = &data->forks[0];
	else
		philo.fork_r = &data->forks[index + 1];
	philo.time_last_eaten = 0;
	philo.times_eaten = 0;
	return (philo);
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
	int	index;

	zero_data(data);
	data->philos = ft_calloc(params.philo_count + 1, sizeof(t_philo));
	if (data->philos == NULL)
		return (printf("Error: allocation failed.\n"), ERROR);
	data->threads = ft_calloc(params.philo_count + 1, sizeof(pthread_t));
	if (data->threads == NULL)
		return (free_data(data), printf("Error: allocation failed.\n"), ERROR);
	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
		return (free_data(data), printf("Error: mutex_init failed.\n"), ERROR);
	if (init_mutex_arr(params.philo_count, &data->forks) == ERROR)
		return (free_data(data), ERROR);
	index = 0;
	while (index++ < params.philo_count)
		data->philos[index - 1] = init_philo(params, data, index - 1);
	return (SUCCESS);
}
