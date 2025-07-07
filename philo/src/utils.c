/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:26:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 21:00:18 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
 * @brief Allocates zero-initialized memory with error handling.
 *
 * Allocates memory for an array of nmemb elements of size bytes each,
 * initializing all bytes to zero. Returns NULL on allocation failure.
 *
 * @param nmemb Number of elements.
 * @param size Size in bytes of each element.
 *
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*w_calloc(size_t nmemb, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(nmemb * size);
	if (!new_ptr)
	{
		error_msg("memory allocation failed", NULL);
		return (NULL);
	}
	memset(new_ptr, 0, nmemb * size);
	return (new_ptr);
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

/**
 * @brief Wrapper for pthread mutex operations with error handling.
 *
 * Locks or unlocks a mutex based on the action parameter. Logs error and
 * returns ERROR if the operation fails.
 *
 * @param action The mutex operation to perform (LOCK or UNLOCK).
 * @param mutex Pointer to the pthread_mutex_t to operate on.
 *
 * @return SUCCESS on success, ERROR on failure.
 */
t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex)
{
	if (!mutex)
	{
		error_msg("missing parameters", "w_mutex");
		return (ERROR);
	}
	if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex) == 0)
			return (SUCCESS);
		error_msg("failed to lock a mutex", NULL);
		return (ERROR);
	}
	if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) == 0)
			return (SUCCESS);
		error_msg("failed to unlock a mutex", NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Locks or unlocks all fork mutexes in the program.
 *
 * Iterates through all fork mutexes and performs the specified action.
 *
 * @param action The mutex operation to perform (LOCK or UNLOCK).
 * @param program Pointer to the main program structure.
 *
 * @return SUCCESS if all operations succeed, ERROR otherwise.
 */
t_error	all_forks(t_mutex_action action, t_program *program)
{
	pthread_mutex_t	**forks;
	t_ms			fork_index;
	t_ms			fork_count;

	if (!program)
	{
		error_msg("missing parameters", "all_forks");
		return (ERROR);
	}
	forks = program->mutexes.forks;
	fork_index = 0;
	fork_count = program->philo_count;
	while (fork_index < fork_count)
	{
		if (w_mutex(action, forks[fork_index]) != SUCCESS)
			return (ERROR);
		fork_index++;
	}
	return (SUCCESS);
}
