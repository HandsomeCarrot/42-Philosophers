/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:10:58 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:15:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Wrapper function for pthread mutex operations with error handling.
 *
 * Provides a safe way to perform mutex lock/unlock operations with proper
 * error checking and reporting. Returns SUCCESS on successful operation,
 * ERROR on failure.
 *
 * @param action The mutex operation to perform (LOCK or UNLOCK)
 * @param mutex Pointer to the mutex to operate on
 * @return t_error SUCCESS if operation succeeded, ERROR if failed
 * @note This function will log an error message if the operation fails
 * @warning The mutex parameter must not be NULL
 */
t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex)
{
	if (!mutex)
		return (error_msg("missing parameters", "w_mutex"));
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
