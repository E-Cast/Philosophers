/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p->c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:42:06 by ecastong          #+#    #+#             */
/*   Updated: 2024/05/05 12:03:01 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_count(int argc)
{
	if (argc >= 5 && argc <= 6)
		return (EXIT_SUCCESS);
	if (argc < 5)
		write(STDERR_FILENO, "Error: not enough arguments\n", 28);
	else if (argc > 6)
		write(STDERR_FILENO, "Error: too many arguments\n", 26);
	write(STDERR_FILENO, "Format: ./philo\n", 16);
	write(STDERR_FILENO, "<philosopher_count>\n", 22);
	write(STDERR_FILENO, "<time_to_die>\n", 15);
	write(STDERR_FILENO, "<time_to_eat>\n", 15);
	write(STDERR_FILENO, "<time_to_sleep>\n", 17);
	write(STDERR_FILENO, "[times_eaten]\n", 32);
	return (EXIT_FAILURE);
}

int	check_params(t_params *p)
{
	int	check;

	check = 0;
	if (p->philo_count < MIN_PHILO_COUNT)
		check += printf("Error: <philosopher_count> is too low\nMin: %i\n",
				MIN_PHILO_COUNT);
	if (p->philo_count > MAX_PHILO_COUNT)
		check += printf("Error: <philosopher_count> is too high\nMax: %i\n",
				MAX_PHILO_COUNT);
	if (p->time_to_die < MIN_TIME_TO_DIE)
		check += printf("Error: <time_to_die> is too low\nMin: %i\n",
				MIN_TIME_TO_DIE);
	if (p->time_to_eat < MIN_TIME_TO_EAT)
		check += printf("Error: <time_to_eat> is too low\nMin: %i\n",
				MIN_TIME_TO_EAT);
	if (p->time_to_sleep < MIN_TIME_TO_SLEEP)
		check += printf("Error: <time_to_sleep> is too low\nMin: %i\n",
				MIN_TIME_TO_SLEEP);
	if (check != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_params(t_params *p, int argc, char **argv)
{
	if (check_arg_count(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	p->philo_count = ph_atoui(argv[1]);
	p->time_to_die = ph_atoui(argv[2]);
	p->time_to_eat = ph_atoui(argv[3]);
	p->time_to_sleep = ph_atoui(argv[4]);
	p->times_eaten = DEFAULT_TIMES_EATEN_TO_END;
	// if (argc == 6)
	// 	p->times_eaten_to_end = ph_atoui(argv[5]);
	// printf("count:%i\ndie:%i\neat:%i\nsleep:%i\nend:%i\n", p->philo_count, p->time_to_die, p->time_to_eat, p->time_to_sleep, p->times_eaten);
	return (check_params(p));
}
