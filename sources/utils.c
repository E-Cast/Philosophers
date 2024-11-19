/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 07:42:33 by ecastong          #+#    #+#             */
/*   Updated: 2024/11/19 12:11:41 by ecastong         ###   ########.fr       */
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
