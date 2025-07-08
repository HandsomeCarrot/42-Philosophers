/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:05:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 16:21:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
char	*ms_to_str(t_ms number)
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

/**
 * @brief Converts a string to an unsigned 64-bit integer with validation.
 *
 * Parses a numeric string and converts it to t_ms, performing validation
 * and overflow checks. Returns ERROR on invalid input.
 *
 * @param str Null-terminated string containing numeric characters.
 * @param result Pointer to t_ms to store the converted value.
 *
 * @return SUCCESS on valid conversion, ERROR otherwise.
 *
 * @note Displays error messages on invalid input.
 */
t_error	atoms(const char *str, t_ms *result)
{
	t_ms	res;
	t_ms	prev;
	char	*nptr;

	res = 0;
	nptr = (char *)str;
	while (nptr && *nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			error_msg("Non-numeric character in argument", (char *)str);
			return (ERROR);
		}
		prev = res;
		res = res * 10 + (*nptr - '0');
		if (res < prev)
		{
			error_msg("number is too large", (char *)str);
			return (ERROR);
		}
		nptr++;
	}
	*result = res;
	return (SUCCESS);
}

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * Counts characters in the string until the null terminator is reached.
 * Returns 0 if str is NULL.
 *
 * @param str Pointer to the null-terminated string.
 *
 * @return Number of characters in the string, excluding the null terminator.
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
