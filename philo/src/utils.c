/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 01:21:53 by vpoka            ###   ########.fr       */
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

// docs
void	*w_calloc(size_t nmemb, size_t size, t_program *program)
{
	void	*new_ptr;

	new_ptr = malloc(nmemb * size);
	if (!new_ptr)
	{
		error_msg("memory allocation failed", NULL);
		exit_philo(ERROR, program);
	}
	memset(new_ptr, 0, nmemb * size);
	return (new_ptr);
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
 * @brief Gets current time in milliseconds and stores in provided pointer.
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
int	get_time_in_ms(t_ms *ms_ptr, t_program *program)
{
	struct timeval	tv;
	t_ms			current_time;

	if (!ms_ptr)
		return (ERROR);
	if (gettimeofday(&tv, NULL) != SUCCESS)
	{
		set_error(ERROR, program);
		safe_putstr_fd("failed to get time\n", STDERR_FILENO, 3, program->mutexes->print);
		return (ERROR);
	}
	current_time = (t_ms)(tv.tv_sec * 1000);
	current_time += (t_ms)(tv.tv_usec / 1000);
	*ms_ptr = current_time;
	return (SUCCESS);
}
