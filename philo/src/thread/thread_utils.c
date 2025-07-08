/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:40:08 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 12:44:50 by vpoka            ###   ########.fr       */
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
t_error	get_time_in_ms(t_ms *ms_ptr, t_mutexes *mutexes)
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

/**
 * @brief Sets the thread termination flag in a thread-safe manner.
 *
 * Acquires the term_flag mutex before writing to the termination flag variable.
 *
 * @param term_flag_ptr Pointer to the termination flag.
 * @param mutexes Pointer to the mutexes structure containing the term_flag mutex.
 */
void	terminate_threads(bool *term_flag_ptr, t_mutexes *mutexes)
{
	if (!mutexes || !term_flag_ptr || !mutexes)
		return ;
	w_mutex(LOCK, mutexes->term_flag);
	*term_flag_ptr = true;
	w_mutex(UNLOCK, mutexes->term_flag);
}

/**
 * @brief Sets the thread termination flag in a thread-safe manner.
 *
 * Acquires the term_flag mutex before writing to the termination flag variable.
 *
 * @param term_flag_ptr Pointer to the termination flag.
 * @param mutexes Pointer to the mutexes structure containing the term_flag mutex.
 */
bool	is_termination_requested(bool *term_flag_ptr, t_mutexes *mutexes)
{
	bool	term_flag;

	if (!term_flag_ptr || !mutexes)
		return (true);
	if (w_mutex(LOCK, mutexes->term_flag))
		return (true);
	term_flag = *term_flag_ptr;
	if (w_mutex(UNLOCK, mutexes->term_flag))
		return (true);
	return (term_flag);
}

/**
 * @brief Handles thread errors by setting the termination flag
 * and returning error.
 *
 * Sets the termination flag to signal other threads to stop and returns
 * an error value.
 *
 * @param term_flag_ptr Pointer to the termination flag.
 * @param mutexes Pointer to the mutexes structure containing the term_flag mutex.
 *
 * @return Always returns (void*)ERROR.
 */
void	*thread_error(bool *term_flag_ptr, t_mutexes *mutexes)
{
	if (!term_flag_ptr || !mutexes)
	{
		error_msg("missing parameters", "thread_error");
		return ((void *)ERROR);
	}
	terminate_threads(term_flag_ptr, mutexes);
	return ((void *)ERROR);
}

/**
 * @brief Waits for simulation start by locking and unlocking a mutex.
 *
 * Synchronizes thread startup by briefly acquiring and releasing a mutex.
 *
 * @param mutex Pointer to the pthread_mutex_t used for synchronization.
 *
 * @return SUCCESS if mutex operations succeed, ERROR otherwise.
 */
t_error	wait_for_start(pthread_mutex_t *mutex)
{
	if (w_mutex(LOCK, mutex) != SUCCESS)
		return (ERROR);
	if (w_mutex(UNLOCK, mutex) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
