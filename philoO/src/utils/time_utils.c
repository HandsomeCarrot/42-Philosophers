/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:13:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 19:35:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Retrieves the current system time in milliseconds since the Unix epoch.
 *
 * This function uses gettimeofday to obtain the current time and converts it
 * to milliseconds. The result is stored in the provided pointer.
 *
 * @param ms_ptr Pointer to a t_ms variable where the current time will be
 *        stored.
 *
 * @return SUCCESS if the time was successfully retrieved, ERROR otherwise.
 *
 * @note The function returns ERROR if ms_ptr is NULL or if gettimeofday fails.
 */
t_error	get_current_time_ms(t_ms *ms_ptr)
{
	struct timeval	tv;
	t_ms			current_time;

	if (!ms_ptr)
		return (error_msg("missing parameters", "get_current_time_ms"));
	if (gettimeofday(&tv, NULL) != SUCCESS)
		return (error_msg("failed to get time", NULL));
	current_time = (t_ms)(tv.tv_sec * 1000);
	current_time += (t_ms)(tv.tv_usec / 1000);
	*ms_ptr = current_time;
	return (SUCCESS);
}

/**
 * @brief Validates that the first timestamp is not greater than the second.
 *
 * Checks if the provided timestamps are in a logical order. Returns ERROR
 * if the first (smaller_timestamp) is greater than the second
 * (larger_timestamp).
 *
 * @param smaller_timestamp The timestamp expected to be less than or equal to
 *        the larger timestamp.
 * @param larger_timestamp The timestamp expected to be greater than or equal to
 *        the smaller timestamp.
 *
 * @return SUCCESS if the timestamps are valid, ERROR otherwise.
 *
 * @note Intended to catch logic errors in timestamp calculations.
 */
static t_error	validate_timestamps(t_ms smaller_timestamp, t_ms larger_timestamp)
{
	if (larger_timestamp < smaller_timestamp)
	{
		error_msg("timestamps do not make sense",
			"smaller_timestamp is larger then the larger_timestamp");
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Calculates the elapsed time in milliseconds since the simulation start.
 *
 * Retrieves the current time and subtracts the simulation start time to
 * determine the elapsed time. The result is stored in the provided pointer.
 *
 * @param ms_ptr Pointer to a t_ms variable where the elapsed time will be
 *        stored.
 * @param input Pointer to the input structure containing the simulation start
 *        time.
 *
 * @return SUCCESS if the elapsed time was successfully calculated, ERROR
 *         otherwise.
 *
 * @note Returns ERROR if ms_ptr or input is NULL, or if time retrieval fails.
 */
t_error	get_elapsed_time(t_ms *ms_ptr, t_input *input)
{
	t_ms	current_time;

	if (!ms_ptr || !input)
	{
		error_msg("missing parameters", "get_elapsed_time");
		return (ERROR);
	}
	if (get_current_time_ms(&current_time))
		return (ERROR);
	if (validate_timestamps(input->sim_start_time, current_time))
		return (ERROR);
	*ms_ptr = current_time - input->sim_start_time;
	return (SUCCESS);
}
