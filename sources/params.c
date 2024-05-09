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
		printf("Error: not enough arguments\n");
	else if (argc > 6)
		printf("Error: too many arguments\n");
	printf("Format: ./philo\n");
	printf("<philosopher_count>\n");
	printf("<time_to_die>\n");
	printf("<time_to_eat>\n");
	printf("<time_to_sleep>\n");
	printf("[times_eaten]\n");
	return (EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		num;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] && str[i] == '-')
		sign = -1;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - 48) * sign;
		i++;
	}
	return (num);
}

int	check_params(t_params *p, int argc)
{
	int	retval;

	retval = 0;
	if (p->philo_count < MIN_PHILO_COUNT)
		retval += printf("Error: <philosopher_count> is too low\nMin: %i\n",
				MIN_PHILO_COUNT);
	if (p->philo_count > MAX_PHILO_COUNT)
		retval += printf("Error: <philosopher_count> is too high\nMax: %i\n",
				MAX_PHILO_COUNT);
	if (p->time_to_die < MIN_TIME_TO_DIE)
		retval += printf("Error: <time_to_die> is too low\nMin: %i\n",
				MIN_TIME_TO_DIE);
	if (p->time_to_eat < MIN_TIME_TO_EAT)
		retval += printf("Error: <time_to_eat> is too low\nMin: %i\n",
				MIN_TIME_TO_EAT);
	if (p->time_to_sleep < MIN_TIME_TO_SLEEP)
		retval += printf("Error: <time_to_sleep> is too low\nMin: %i\n",
				MIN_TIME_TO_SLEEP);
	if (argc == 6 && p->times_eaten < 0 && retval == 0)
	{
		printf("Warning: <times_eaten> is smaller than 0\n");
		printf("Parameter will go unused\n");
	}
	return (retval);
}

int	set_params(t_params *p, int argc, char **argv)
{
	if (check_arg_count(argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	p->philo_count = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	p->times_eaten = DEFAULT_TIMES_EATEN_TO_END;
	if (argc == 6)
		p->times_eaten = ft_atoi(argv[5]);
	// printf("count:%i\ndie:%i\neat:%i\nsleep:%i\nend:%i\n", p->philo_count, p->time_to_die, p->time_to_eat, p->time_to_sleep, p->times_eaten);
	return (check_params(p, argc));
}
