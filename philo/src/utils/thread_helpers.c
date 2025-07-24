/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:18:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 00:55:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Set the termination flag in a thread-safe manner.
 *
 * This function locks the provided mutex, sets the termination 
 * flag to true, and then unlocks the mutex. This ensures that 
 * the termination signal is safely communicated across threads.
 *
 * @param term_flag_ptr Pointer to a boolean variable indicating the 
 *        termination state to be set.
 * @param mutex Pointer to a pthread_mutex_t used for synchronizing 
 *        access to the termination flag.
 *
 * @note Call this function when a thread decides that the simulation 
 *       should be terminated. This will alert all participating 
 *       threads in a synchronized fashion.
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
 * @brief Check if the termination flag has been set in a thread-safe manner.
 *
 * This function acquires the given mutex, reads the value of the 
 * termination flag, then releases the mutex, ensuring consistent 
 * visibility of the flag across threads.
 *
 * @param term_flag_ptr Pointer to a boolean variable containing the 
 *        termination state.
 * @param mutex Pointer to a pthread_mutex_t used for synchronizing 
 *        access to the termination flag.
 *
 * @return true if the termination has been requested, false otherwise.
 *
 * @warning If either argument is NULL, this function prints an error 
 *          and returns true to trigger safe termination.
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
 * @brief Wait for the simulation start signal using a synchronization mutex.
 *
 * Locks and immediately unlocks the provided mutex, effectively causing 
 * the thread to pause until another thread signals that the simulation 
 * should begin. This pattern is used to synchronize the start of all 
 * simulation threads.
 *
 * @param mutex Pointer to a pthread_mutex_t start synchronization mutex.
 *
 * @return SUCCESS if the operation completes without error, ERROR otherwise.
 *
 * @note All simulation threads should call this function before starting 
 *       their core execution logic, to ensure coordinated startup.
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
