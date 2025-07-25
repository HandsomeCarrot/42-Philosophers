/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:53:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 15:22:58 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Converts a string to milliseconds with validation
 *
 * Parses a string into a t_ms (milliseconds) value with full validation:
 * - Checks for non-numeric characters
 * - Checks for overflow
 * - Returns error messages for invalid input
 *
 * @param str The input string to convert
 * @param result Pointer to store the converted value
 * @return t_error SUCCESS on valid conversion, ERROR on failure
 */
static t_error	atoms(const char *str, t_ms *result)
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
			error_msg("number is too large (uint64)", (char *)str);
			return (ERROR);
		}
		nptr++;
	}
	*result = res;
	return (SUCCESS);
}

/**
 * @brief Converts a string to philosopher count with validation
 *
 * Parses a string into a t_count (philosopher count) value with validation:
 * - Checks for non-numeric characters
 * - Checks for overflow
 * - Returns error messages for invalid input
 *
 * @param str The input string to convert
 * @param result Pointer to store the converted value
 * @return t_error SUCCESS on valid conversion, ERROR on failure
 */
static t_error	atocount(const char *str, t_count *result)
{
	t_count	res;
	t_count	prev;
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
			error_msg("number is too large (uint16)", (char *)str);
			return (ERROR);
		}
		nptr++;
	}
	*result = res;
	return (SUCCESS);
}

/**
 * @brief Processes and validates philosopher count and meal limit
 *
 * Validates and stores:
 * - Philosopher count (must be at least 1)
 * - Optional meal limit (if meal_limit parameter is true)
 *
 * @param meal_limit Flag indicating if meal limit is provided
 * @param argv Command line arguments array
 * @param data Pointer to simulation data structure
 * @return t_error SUCCESS on valid input, ERROR on failure
 */
static t_error	get_counts(bool meal_limit, char **argv, t_data *data)
{
	if (atocount((const char *)argv[1], &data->input.philo_count) != SUCCESS)
		return (ERROR);
	if (data->input.philo_count < 1)
		return (error_msg("Incorrect input", "needs at least 1 philosopher"));
	if (meal_limit)
	{
		if (atocount((const char *)argv[5], &data->input.meal_limit) != SUCCESS)
			return (ERROR);
		data->input.has_meal_limit = true;
	}
	return (SUCCESS);
}

/**
 * @brief Processes and validates time parameters
 *
 * Validates and stores time parameters:
 * - Time to die
 * - Time to eat
 * - Time to sleep
 * - Time to think
 *
 * @param argv Command line arguments array
 * @param data Pointer to simulation data structure
 * @return t_error SUCCESS on valid input, ERROR on failure
 */
static t_error	get_times(char **argv, t_data *data)
{
	t_ms	think_time;
	t_ms	total;

	if (atoms((const char *)argv[2], &data->input.time_to_die) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[3], &data->input.time_to_eat) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[4], &data->input.time_to_sleep) != SUCCESS)
		return (ERROR);
	if (data->input.time_to_eat > data->input.time_to_die ||
		data->input.time_to_sleep > data->input.time_to_die)
		return (SUCCESS);
	total = data->input.time_to_die - data->input.time_to_eat - data->input.time_to_sleep;
	if (total < 20)
		think_time = 0;
	else
		think_time = (total / 2) - 10;
	data->input.time_to_think = think_time;
	return (SUCCESS);
}

/**
 * @brief Main input processing function
 *
 * Coordinates the processing of all input parameters:
 * - Validates input pointers
 * - Calls get_counts and get_times
 * - Returns consolidated error status
 *
 * @param meal_limit Flag indicating if meal limit is provided
 * @param argv Command line arguments array
 * @param data Pointer to simulation data structure
 * @return t_error SUCCESS if all inputs are valid, ERROR otherwise
 */
t_error	proccess_input(bool meal_limit, char **argv, t_data *data)
{
	if (!argv || !data)
		return (error_msg("missing parameters", "process_input"));
	if (get_counts(meal_limit, argv, data) != SUCCESS)
		return (ERROR);
	if (get_times(argv, data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
