/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mstoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:53:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 20:56:35 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Counts the number of digits in a t_ms value.
 *
 * Calculates the number of decimal digits required to represent the given
 * unsigned integer.
 *
 * @param number The t_ms value whose digits are to be counted.
 *
 * @return The number of digits in the t_ms value.
 */
static int	count_nums(t_ms number)
{
	int	digit_count;

	digit_count = 0;
	if (number == 0)
		return (1);
	while (number > 0)
	{
		number /= 10;
		digit_count++;
	}
	return (digit_count);
}

/**
 * @brief Converts a t_ms value to a null-terminated string.
 *
 * Converts the given t_ms value to its string representation. The result is
 * dynamically allocated and must be freed by the caller.
 *
 * @param number The t_ms value to convert.
 *
 * @return Pointer to the allocated string, or NULL on allocation failure.
 *
 * @note The caller is responsible for freeing the returned string.
 */
char	*mstoa(t_ms number)
{
	char	*digit_str;
	int		digit_count;

	digit_count = count_nums(number);
	digit_str = malloc((digit_count + 1) * sizeof(char));
	if (!digit_str)
		return (NULL);
	digit_str[digit_count] = 0;
	if (number == 0)
	{
		digit_str[0] = '0';
		return (digit_str);
	}
	while (number > 0)
	{
		digit_count--;
		digit_str[digit_count] = (number % 10) + '0';
		number /= 10;
	}
	return (digit_str);
}
