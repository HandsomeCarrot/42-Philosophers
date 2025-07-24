/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:13:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:01:21 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Gets the current time in milliseconds since epoch.
 *
 * Retrieves the current system time using gettimeofday() and converts it
 * to milliseconds. The result is stored in the provided pointer.
 *
 * @param ms_ptr Pointer to store the current time in milliseconds.
 * @return SUCCESS on success, ERROR on failure (invalid input or system error).
 * @note The ms_ptr parameter must not be NULL.
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
 * @brief Validates that two timestamps are in chronological order.
 *
 * Ensures that the newer_timestamp is actually newer than the older_timestamp.
 * This is used to prevent logical errors with time calculations.
 *
 * @param older_timestamp The timestamp that should be older.
 * @param newer_timestamp The timestamp that should be newer.
 * @return SUCCESS if timestamps are valid, ERROR if they are out of order.
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

/**
 * @brief Calculates the time elapsed since a given start time.
 *
 * Gets the current time and calculates the difference from the provided
 * start time. The result is stored in ms_ptr after validation.
 *
 * @param ms_ptr Pointer to store the elapsed time in milliseconds.
 * @param start_time The reference start time in milliseconds.
 * @return SUCCESS on success, ERROR on failure (invalid input or time error).
 * @note Both parameters must be valid and timestamps must be in order.
 */
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

/**
 * @brief Sleeps for a precise amount of time in milliseconds.
 *
 * Implements a more precise sleep than standard usleep by using a loop
 * with progressively smaller sleep intervals to minimize oversleeping.
 *
 * @param sleep_time_ms The duration to sleep in milliseconds.
 * @return SUCCESS on success, ERROR on failure (time retrieval error).
 * @note For very short sleeps (<10ms), uses a single usleep call.
 * @warning Not perfectly precise due to system scheduling limitations.
 */
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

/**
 * @brief Sleeps for a duration while checking for termination requests.
 *
 * Sleeps in intervals while periodically checking if termination has been
 * requested. This allows the thread to respond quickly to termination signals.
 *
 * @param time The total time to sleep in milliseconds.
 * @param philo Pointer to the philosopher's data structure.
 * @return SUCCESS on completion, TERMINATE if termination requested,
 *         ERROR on sleep failure.
 * @note Uses SLEEP_INTERVAL constant for check frequency.
 * @warning Must have valid philo pointer with termination flag and mutex.
 */
t_error	thread_sleep(t_ms time, t_philo *philo)
{
	t_ms	interval;
	t_ms	sleep_time;

	interval = SLEEP_INTERVAL;
	while (time > 0)
	{
		if (time < interval)
			sleep_time = time;
		else
			sleep_time = interval;
		if (precise_sleep(sleep_time) != 0)
			return (error_msg("failed to sleep", "thread_sleep"));
		if (termination_requested(philo->term_flag, philo->mutexes.term_flag))
			return (TERMINATE);
		time -= sleep_time;
	}
	return (SUCCESS);
}
