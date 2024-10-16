/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:48:05 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/16 18:46:16 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Frees the t_data struct's allocated members and sets them to NULL.
 * 
 * @param data Struct with the members to free.
 */
void	free_data(t_data **data)
{
	free((*data)->philos);
	(*data)->philos = NULL;
	free((*data)->threads);
	(*data)->threads = NULL;
	free((*data)->forks);
	(*data)->forks = NULL;
	free((*data)->info_lock);
	(*data)->info_lock = NULL;
	free(*data);
	*data = NULL;
}

/**
 * @brief Allocates a struct of mutexes and initializes all of them.
 * 
 * @param n Number of mutexes to put inside the array.
 * @param arr Array to initialize.
 * @retval 0 on success.
 * @retval -1 on error.
 */
static int	init_mutex_arr(size_t n, t_mutex **arr)
{
	size_t	index;
	t_mutex	*array;

	array = ft_calloc(n + 1, sizeof(t_mutex));
	if (array == NULL)
		return (printf("Error: allocation failed.\n"), -1);
	index = 0;
	while (index < n)
	{
		if (pthread_mutex_init(&array[index], NULL) != 0)
		{
			printf("Error: mutex_init failed.\n");
			return (free(array), -1);
		}
		index++;
	}
	return (*arr = array, 0);
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

	philo.mic_lock = &data->mic_lock;
	philo.mic_state = &data->mic_state;
	philo.fork_l = &data->forks[index];
	if (params.philo_count == 1)
		philo.fork_r = NULL;
	else if (index + 1 == params.philo_count)
		philo.fork_r = &data->forks[0];
	else
		philo.fork_r = &data->forks[index + 1];
	philo.info_lock = &data->info_lock[index];

	philo.state = RUNNING;
	philo.time_last_eaten = 0;
	philo.times_eaten = 0;
	return (philo);
}

/**
 * @brief Allocates and initializes the data struct and it's members.
 * 
 * @param params Struct containing the parameters used in the initialization.
 * @param data Struct to initialize.
 * @retval 0 on success.
 * @retval -1 on error.
 */
int	init_data(t_params params, t_data *data)
{
	int	index;

	data->params = params;
	data->philos = ft_calloc(params.philo_count + 1, sizeof(t_philo));
	if (data->philos == NULL)
		return (free_data(&data), printf("Error: allocation failed.\n"), -1);
	data->threads = ft_calloc(params.philo_count + 1, sizeof(pthread_t));
	if (data->threads == NULL)
		return (free_data(&data), printf("Error: allocation failed.\n"), -1);

	if (pthread_mutex_init(&data->mic_lock, NULL) != 0)
		return (free_data(&data), -1);
	data->mic_state = RUNNING;

	if (init_mutex_arr(params.philo_count, &data->forks) == -1)
		return (free_data(&data), -1);
	if (init_mutex_arr(params.philo_count, &data->info_lock) == -1)
		return (free_data(&data), -1);

	index = 0;
	while (index++ < params.philo_count)
		data->philos[index - 1] = init_philo(params, data, index - 1);
	return (0);
}
