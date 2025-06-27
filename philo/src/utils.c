/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 19:03:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Converts a string to a t_ms (uint64_t) with error checking.
 *
 * Parses the input string character by character, converting it to a
 * t_ms value. Performs validation to ensure all characters
 * are digits and the resulting value doesn't overflow.
 *
 * @param str The string to convert to a t_ms.
 * @param error Pointer to an bool that will be set to true if
 *              conversion fails (non-numeric chars or overflow).
 * @return The converted t_ms value, or 0 on error.
 * @note Sets error flag and prints message if invalid input is detected.
 * @warning Caller must check the error flag to verify successful conversion.
 */
t_ms	ft_atoms(const char *str, bool *error)
{
	uint64_t	res;
	uint64_t	prev;
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
		prev = res;
		res = res * 10 + (*nptr - '0');
		if (res < prev)
		{
			error_msg("argument is too large", (char *)str);
			*error = true;
			return (0);
		}
		nptr++;
	}
	return (res);
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

/**
 * @brief Gets the current time in milliseconds and stores it in the provided pointer.
 *
 * Retrieves the current system time using gettimeofday() and converts it to
 * milliseconds (combining seconds and microseconds components). The result is
 * stored in the provided t_ms pointer.
 *
 * @param ms_ptr Pointer to a t_ms variable where the current time in ms will
 *               be stored. Must not be NULL.
 * @return SUCCESS (0) if time was successfully retrieved and stored,
 *         ERROR (1) if ms_ptr is NULL or gettimeofday() fails.
 * @note The function handles the conversion from seconds+microseconds to
 *       milliseconds internally.
 * @warning The caller must ensure ms_ptr is a valid pointer to a t_ms variable.
 */
int	get_time_in_ms(t_ms *ms_ptr)
{
	struct timeval	tv;
	t_ms			current_time;

	if (!ms_ptr)
		return (ERROR);
	if (gettimeofday(&tv, NULL) != SUCCESS)
	{
		// safe_putstr() "failed to get time"
		return (ERROR);
	}
	current_time = (t_ms)(tv.tv_sec * 1000);
	current_time += (t_ms)(tv.tv_usec / 1000);
	*ms_ptr = current_time;
	return (SUCCESS);
}

// docs
// TODO
char	*ft_mstoa(t_ms nbr)
{
	(void)nbr;
	return (NULL);
}
