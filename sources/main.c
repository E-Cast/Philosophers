/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/15 19:12:14 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		*data;

	if (argc < 5)
		return (printf("Error: too few arguments\n"), -1);
	if (get_params(argc, argv, &params) == -1)
		return (-1);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (printf("Error: allocation failed.\n"), -1);
	if (init_data(params, data) == -1)
		return (-1);

	if (launch_threads(params.philo_count, data->threads, data->philos) == -1)
		return (free_data(&data), -1);
	//launch monitor

	wait_threads(params.philo_count, data->threads);
	return (free_data(&data), 0);
}
