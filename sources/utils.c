/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 07:42:33 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 11:09:21 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Ensures the pointer isn't NULL before calling the function on it.
 * 
 * @param mutex_ptr Mutex pointer to call the function on.
 * @param mutex_func Function to be called.
 * @retval The function's return value
 * @retval -1 if the pointer is NULL.
 */
int	safe_mutex(t_mutex *mutex_ptr, int (mutex_func)(t_mutex *))//probably unecessary
{
	if (mutex_ptr != NULL)
		return (mutex_func(mutex_ptr));
	return (-1);
}

/**
 * @brief Converts an ascii string to an integer.
 * 
 * @param str String to convert.
 * @retval An integer inbetween INT_MIN and INT_MAX inclusive.
 * @retval 0 if the string isn't valid.
 */
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

/**
 * @brief Allocates enough space for a pointer with count objects of
 * 	size size. Writes 0 to every bite of the pointer.
 * 
 * @param count Number of objects.
 * @param size Size of objects.
 * @retval A valid pointer on success.
 * @retval Null on error.
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (printf("Error: allocation failed.\n"), NULL);
	memset(ptr, 0, count * size);
	return ((void *)ptr);
}
