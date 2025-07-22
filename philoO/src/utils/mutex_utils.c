/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:10:58 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/22 22:47:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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
