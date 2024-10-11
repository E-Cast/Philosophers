/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:27:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/10/07 09:03:22 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char **argv)
{
	t_params	params;

	if (argc < 5)
		return (printf("Error: too few arguments\n"), ERROR);
	if (get_params(argc, argv, &params) == ERROR)
		return (ERROR);
	printf("%i\n%i\n%i\n%i\n%i\n", params.philo_count, params.time_to_die, params.time_to_eat, params.time_to_sleep, params.times_to_eat);
	log_msg(-1, 1, MSG_DIE);
	return (SUCCESS);
}
