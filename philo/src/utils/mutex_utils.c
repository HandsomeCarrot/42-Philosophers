/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:10:58 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/10 12:35:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
 * Iterates through all fork mutexes and performs the specified action
 * (LOCK or UNLOCK) on each.
 *
 * @param action The mutex operation to perform (LOCK or UNLOCK).
 * @param program Pointer to the main program structure containing the
 *        mutexes.
 *
 * @return SUCCESS if all operations succeed, ERROR otherwise.
 *
 * @note Returns ERROR if the program pointer is NULL or if any mutex
 *       operation fails.
 */
t_error	mutex_all_forks(t_mutex_action action, t_program *program)
{
	pthread_mutex_t	**forks;
	t_ms			fork_index;
	t_ms			fork_count;

	if (!program)
	{
		error_msg("missing parameters", "mutex_all_forks");
		return (ERROR);
	}
	forks = program->mutexes.forks;
	fork_index = 0;
	fork_count = program->input.philo_count;
	while (fork_index < fork_count)
	{
		if (w_mutex(action, forks[fork_index]) != SUCCESS)
			return (ERROR);
		fork_index++;
	}
	return (SUCCESS);
}
