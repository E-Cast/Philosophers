/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/14 15:01:26 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;

	if (argc < 5)
		return (printf("Error: too few arguments\n"), ERROR);
	if (get_params(argc, argv, &params) == ERROR)
		return (ERROR);
	if (init_data(params, &data) == ERROR)
		return (ERROR);

	if (launch_threads(params.philo_count, data))
		return (free_data(&data), ERROR);
	// launch all threads
	// 		free philo and return on error
	wait_threads(params.philo_count, data.threads);
	return (free_data(&data), SUCCESS);
}
