/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:03:15 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/15 18:51:01 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Extracts parameters from user provided command line arguments.
 * 
 * @param argc Number of arguments.
 * @param argv Array of arguments as strings.
 * @param params Struct to store the parameters in.
 * @retval SUCCESS on success.
 * @retval ERROR on error.
 */
int	get_params(int argc, char **argv, t_params *params)
{
	t_params	p_tmp;

	p_tmp.philo_count = ft_atoi(argv[1]);
	if (!(p_tmp.philo_count >= 1 && p_tmp.philo_count <= 200))
		return (printf("Error: philo_count must be 1 from to 200\n"), ERROR);
	p_tmp.time_to_die = ft_atoi(argv[2]);
	if (!(p_tmp.time_to_die >= MIN_TIME))
		return (printf("Error: time_to_die too low\n"), ERROR);
	p_tmp.time_to_eat = ft_atoi(argv[3]);
	if (!(p_tmp.time_to_eat >= MIN_TIME))
		return (printf("Error: time_to_eat too low\n"), ERROR);
	p_tmp.time_to_sleep = ft_atoi(argv[4]);
	if (!(p_tmp.time_to_sleep >= MIN_TIME))
		return (printf("Error: time_to_sleep too low\n"), ERROR);
	p_tmp.times_to_eat = 0;
	if (argc > 5)
	{
		p_tmp.times_to_eat = ft_atoi(argv[5]);
		if (!(p_tmp.times_to_eat >= 1))
			return (printf("Error: times_to_eat must be more than 0\n"), ERROR);
	}
	*params = p_tmp;
	return (SUCCESS);
}
