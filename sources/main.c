/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/13 09:59:12 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
{
	t_philo		*philo;
	// t_params	params;

	philo = (t_philo *)arg;
	(void) philo;
	// params = philo->parameters;
	return (NULL);
}

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
	//launch all threads
	//		free philo and return on error
	free_data(&data);
	return (SUCCESS);
}
