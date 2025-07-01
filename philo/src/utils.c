/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 17:22:04 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Converts a string to an unsigned 64-bit integer with validation.
 *
 * This function parses a null-terminated string containing numeric
 * characters and converts it to a t_ms (uint64_t) value. It performs
 * validation to ensure all characters are digits and detects overflow
 * conditions. If any validation fails, the function displays an error
 * message and terminates the program.
 *
 * @param str A null-terminated string containing only numeric characters
 *            to be converted to an unsigned integer.
 * @param program Pointer to the main program structure used for error
 *                handling and program termination.
 *
 * @return The converted unsigned 64-bit integer value from the string.
 *
 * @note This function will terminate the program if non-numeric
 *       characters are found or if overflow is detected.
 * @warning The function modifies program state on error by calling
 *          exit_philo(), which may terminate the entire program.
 */
t_ms	atoms(const char *str, t_program *program)
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
			error_msg("Non-numeric character found in argument", (char *)str);
			exit_philo(ERROR, program);
		}
		prev = res;
		res = res * 10 + (*nptr - '0');
		if (res < prev)
		{
			error_msg("argument is too large", (char *)str);
			exit_philo(ERROR, program);
		}
		nptr++;
	}
	return (res);
}

/**
 * @brief Allocates zero-initialized memory with error handling.
 *
 * This function allocates memory for an array of nmemb elements of size
 * bytes each and initializes all bytes to zero. If memory allocation
 * fails, it displays an error message and terminates the program. This
 * is a wrapper around malloc() and memset() with integrated error
 * handling for the philosophers program.
 *
 * @param nmemb Number of elements to allocate memory for.
 * @param size Size in bytes of each element.
 * @param program Pointer to the main program structure used for error
 *                handling and program termination.
 *
 * @return Pointer to the allocated and zero-initialized memory block.
 *
 * @note This function will terminate the program if memory allocation
 *       fails, ensuring no NULL pointers are returned.
 * @warning The function modifies program state on error by calling
 *          exit_philo(), which may terminate the entire program.
 */
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
 * This function iterates through the provided string counting characters
 * until it encounters a null terminator. It safely handles NULL input
 * by returning 0. This is a custom implementation of the standard
 * strlen() function.
 *
 * @param str Pointer to the null-terminated string whose length is to
 *            be calculated. Can be NULL.
 *
 * @return The number of characters in the string, excluding the null
 *         terminator. Returns 0 if str is NULL.
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
 * @brief Gets the current time in milliseconds since Unix epoch.
 *
 * This function retrieves the current system time using gettimeofday()
 * and converts it to milliseconds since the Unix epoch. The result is
 * stored in the provided pointer. If an error occurs during time
 * retrieval, an error message is displayed with proper mutex protection
 * for thread safety.
 *
 * @param ms_ptr Pointer to a t_ms variable where the current time in
 *               milliseconds will be stored. Must not be NULL.
 * @param mutex Pointer to a mutex used for thread-safe error message
 *              output. Can be NULL if thread safety is not required.
 *
 * @return SUCCESS (0) if the time was successfully retrieved and stored,
 *         ERROR (1) if ms_ptr is NULL or gettimeofday() fails.
 *
 * @note This function is thread-safe when a valid mutex is provided.
 */
int	get_time_in_ms(t_ms *ms_ptr, pthread_mutex_t *mutex)
{
	struct timeval	tv;
	t_ms			current_time;

	if (!ms_ptr)
		return (ERROR);
	if (gettimeofday(&tv, NULL) != SUCCESS && mutex)
	{
		w_mutex(LOCK, mutex);
		error_msg("failed to get time", NULL);
		w_mutex(UNLOCK, mutex);
		return (ERROR);
	}
	current_time = (t_ms)(tv.tv_sec * 1000);
	current_time += (t_ms)(tv.tv_usec / 1000);
	*ms_ptr = current_time;
	return (SUCCESS);
}

/**
 * @brief Wrapper function for pthread mutex operations with error handling.
 *
 * This function provides a unified interface for locking and unlocking
 * pthread mutexes with integrated error handling. If a mutex operation
 * fails, it displays an error message and terminates the program. This
 * ensures that mutex failures are handled consistently throughout the
 * philosophers program.
 *
 * @param action The mutex operation to perform (LOCK or UNLOCK) as
 *               defined by the t_mutex_action enumeration.
 * @param mutex Pointer to the pthread_mutex_t to operate on. If NULL,
 *              the function returns immediately without performing any
 *              operation.
 *
 * @note This function will terminate the program if mutex operations
 *       fail, ensuring consistent error handling.
 * @warning The function modifies program state on error by calling
 *          exit_philo(), which may terminate the entire program.
 * @see t_mutex_action enumeration for valid action values.
 */
void	w_mutex(t_mutex_action action, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (action == LOCK)
	{
		if (!pthread_mutex_lock(mutex))
			return ;
		error_msg("failed to lock a mutex", NULL);
		exit_philo(ERROR, NULL);
	}
	if (action == UNLOCK)
	{
		if (!pthread_mutex_unlock(mutex))
			return ;
		error_msg("failed to unlock a mutex", NULL);
		exit_philo(ERROR, NULL);
	}
}
