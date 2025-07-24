/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:18:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 17:45:40 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Sets the thread termination flag in a thread-safe manner.
 *
 * Acquires the term_flag mutex before writing to the termination flag variable.
 *
 * @param term_flag_ptr Pointer to the termination flag.
 * @param mutexes Pointer to the mutexes structure containing
 * the term_flag mutex.
 */
void	set_termination_flag(bool *term_flag_ptr, pthread_mutex_t *mutex)
{
	if (!term_flag_ptr || !mutex)
		error_msg("missing parameters", "set_termination_flag");
	w_mutex(LOCK, mutex);
	*term_flag_ptr = true;
	w_mutex(UNLOCK, mutex);
}

/**
 * @brief Sets the thread termination flag in a thread-safe manner.
 *
 * Acquires the term_flag mutex before writing to the termination flag variable.
 *
 * @param term_flag_ptr Pointer to the termination flag.
 * @param mutexes Pointer to the mutexes structure containing
 * the term_flag mutex.
 */
bool	termination_requested(bool *term_flag_ptr, pthread_mutex_t *mutex)
{
	bool	term_flag;

	if (!term_flag_ptr || !mutex)
		return (error_msg("missing parameters", "termination_requested"), true);
	if (w_mutex(LOCK, mutex))
		return (true);
	term_flag = *term_flag_ptr;
	if (w_mutex(UNLOCK, mutex))
		return (true);
	return (term_flag);
}

/**
 * @brief Wait for simulation start signal by trying to lock start mutex
 * @param mutex Start synchronization mutex to wait on
 * @return SUCCESS on success, ERROR on failure
 */
t_error	wait_for_start(pthread_mutex_t *mutex)
{
	if (!mutex)
		return (error_msg("missing parameters", "wait_for_start"));
	if (w_mutex(LOCK, mutex) != SUCCESS)
		return (ERROR);
	if (w_mutex(UNLOCK, mutex) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
