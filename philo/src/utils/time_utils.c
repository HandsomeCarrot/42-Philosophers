/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:13:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 16:23:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Gets the current time in milliseconds since Unix epoch.
 *
 * Retrieves the current system time and converts it to milliseconds since
 * the Unix epoch. Stores the result in the provided pointer.
 *
 * @param ms_ptr Pointer to a t_ms variable to store the current time.
 * @param mutexes Pointer to the mutexes structure for thread-safe error
 *                output, can be NULL.
 *
 * @return SUCCESS if time was retrieved, ERROR otherwise.
 *
 * @note Thread-safe when a valid mutex is provided.
 */
t_error	get_current_time_ms(t_ms *ms_ptr, t_mutexes *mutexes)
{
	struct timeval	tv;
	t_ms			current_time;

	if (!ms_ptr)
		return (ERROR);
	if (gettimeofday(&tv, NULL) != SUCCESS && mutexes)
	{
		error_msg("failed to get time", NULL);
		return (ERROR);
	}
	current_time = (t_ms)(tv.tv_sec * 1000);
	current_time += (t_ms)(tv.tv_usec / 1000);
	*ms_ptr = current_time;
	return (SUCCESS);
}

// docs
t_error	get_elapsed_time_ms(t_ms *ms_ptr, t_input *input, t_mutexes *mutexes)
{
	t_ms	current_time;

	if (!ms_ptr || !input)
	{
		error_msg("missing parameters", "get_elapsed_time_ms");
		return (ERROR);
	}
	if (get_current_time_ms(&current_time, mutexes))
		return (ERROR);
	if (current_time > input->sim_start_time)
		return (ERROR);
	*ms_ptr = input->sim_start_time - current_time;
	return (SUCCESS);
}
