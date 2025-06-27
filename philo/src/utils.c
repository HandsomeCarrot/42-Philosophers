/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 16:32:13 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Converts a string to an unsigned integer with error checking.
 *
 * Parses the input string character by character, converting it to an
 * unsigned integer value. Performs validation to ensure all characters
 * are digits and the resulting value doesn't exceed UINT_MAX.
 *
 * @param str The string to convert to an unsigned integer.
 * @param error Pointer to a boolean that will be set to true if
 *              conversion fails (non-numeric chars or overflow).
 * @return The converted unsigned integer value, or 0 on error.
 * @note Sets error flag and prints message if invalid input is detected.
 * @warning Caller must check the error flag to verify successful conversion.
 */
unsigned int	ft_atoui(const char *str, bool *error)
{
	long long	res;
	char		*nptr;

	res = 0;
	nptr = (char *)str;
	while (nptr && *nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			error_msg("Non-numeric character found in argument", (char *)str);
			*error = true;
			return (0);
		}
		res = res * 10 + (*nptr - '0');
		if (res > UINT_MAX)
		{
			error_msg("argument is too large", (char *)str);
			*error = true;
			return (0);
		}
		nptr++;
	}
	return ((unsigned int)res);
}

/**
 * @brief Allocates and zero-initializes memory for an array.
 *
 * Allocates memory for an array of nmemb elements of size bytes each
 * and initializes all bytes to zero. Similar to standard calloc but
 * with direct error checking.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element in bytes.
 * @return Pointer to allocated memory, or NULL if allocation fails.
 * @note Memory is guaranteed to be zero-initialized if allocation succeeds.
 * @warning Returns NULL if allocation fails - caller must check return value.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	memset(res, 0, nmemb * size);
	return (res);
}

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * Counts the number of characters in the string until the null terminator
 * is encountered. Handles NULL pointer input gracefully.
 *
 * @param str The string to measure (may be NULL).
 * @return Length of the string in characters, or 0 if str is NULL.
 * @note Returns 0 for NULL input rather than causing a segmentation fault.
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
