/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:03:15 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 11:07:44 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Extracts parameters from user provided command line arguments.
 * 
 * @param argc Number of arguments.
 * @param argv Array of arguments as strings.
 * @param params Struct to store the parameters in.
 * @retval 0 on success.
 * @retval -1 on error.
 */
int	get_params(int argc, char **argv, t_params *params)
{
	if (argc < 5)
		return (printf("Error: too few arguments\n"), -1);
	params->philo_count = ft_atoi(argv[1]);
	if (!(params->philo_count >= 1 && params->philo_count <= 200))
		return (printf("Error: philo_count must be 1 from to 200\n"), -1);
	params->time_to_die = ft_atoi(argv[2]);
	if (!(params->time_to_die >= MIN_TIME))
		return (printf("Error: time_to_die too low\n"), -1);
	params->time_to_eat = ft_atoi(argv[3]);
	if (!(params->time_to_eat >= MIN_TIME))
		return (printf("Error: time_to_eat too low\n"), -1);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (!(params->time_to_sleep >= MIN_TIME))
		return (printf("Error: time_to_sleep too low\n"), -1);
	params->times_to_eat = 0;
	if (argc > 5)
	{
		params->times_to_eat = ft_atoi(argv[5]);
		if (!(params->times_to_eat >= 1))
			return (printf("Error: times_to_eat must be more than 0\n"), -1);
	}
	return (0);
}
