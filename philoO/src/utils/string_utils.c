/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:05:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 15:18:03 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * Iterates through the characters of the string until the null terminator
 * is found, returning the character count.
 *
 * @param str Pointer to the null-terminated string.
 *
 * @return The number of characters in the string, excluding the null
 *         terminator.
 *
 * @note Returns 0 if str is NULL.
 */
int	ft_strlen(char *str)
{
	int	counter;

	counter = 0;
	while (str && *str)
	{
		counter++;
		str++;
	}
	return (counter);
}
