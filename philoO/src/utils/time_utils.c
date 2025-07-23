/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:13:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 01:05:47 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Retrieves current time in milliseconds since Unix epoch.
 *
 * This function uses gettimeofday to obtain the current system time
 * since the unix epoch and converts it to milliseconds.
 * The result is stored in the provided pointer.
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
 * @brief Validates that the first timestamp is not newer than the second.
 *
 * Checks if the provided timestamps are in a logical order. Returns ERROR
 * if the first (older_timestamp) is newer than the second
 * (newer_timestamp).
 *
 * @param older_timestamp The timestamp expected to be older than or equal to
 *        the newer timestamp.
 * @param newer_timestamp The timestamp expected to be newer than or equal to
 *        the older timestamp.
 *
 * @return SUCCESS if the timestamps are valid, ERROR otherwise.
 *
 * @note Intended to catch logic errors in timestamp calculations.
 */
static t_error	validate_timestamps(t_ms older_timestamp, t_ms newer_timestamp)
{
	if (newer_timestamp < older_timestamp)
	{
		error_msg("timestamps do not make sense",
			"older_timestamp is newer then the newer_timestamp");
		return (ERROR);
	}
	return (SUCCESS);
}

// docs
t_error	get_elapsed_time(t_ms *ms_ptr, t_ms start_time)
{
	t_ms	current_time;

	if (!ms_ptr)
		return (error_msg("missing parameters", "get_elapsed_time"));
	if (get_current_time_ms(&current_time))
		return (ERROR);
	if (validate_timestamps(start_time, current_time))
		return (ERROR);
	*ms_ptr = current_time - start_time;
	return (SUCCESS);
}

/// docs
t_error	precise_sleep(t_ms sleep_time_ms)
{
	t_ms	start;
	t_ms	elapsed;
	t_ms	remaining;

	if (sleep_time_ms == 0)
		return (SUCCESS);
	if (get_current_time_ms(&start) != SUCCESS)
		return (ERROR);
	if (sleep_time_ms > 10 && usleep(sleep_time_ms * 800) != 0)
		return (error_msg("failed initial sleep", "precise_sleep/1"));
	while (1)
	{
		if (get_elapsed_time(&elapsed, start) != SUCCESS)
			return (ERROR);
		if (elapsed >= sleep_time_ms)
			break ;
		remaining = sleep_time_ms - elapsed;
		if (remaining > 1 && usleep((remaining / 2) * MS_TO_USEC) != 0)
			return (error_msg("failed remaining sleep", "precise_sleep/2"));
	}
	return (SUCCESS);
}
