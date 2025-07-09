/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:18:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/09 13:46:25 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Sets the thread termination flag in a thread-safe manner.
 *
 * Acquires the term_flag mutex before writing to the termination flag variable.
 *
 * @param term_flag_ptr Pointer to the termination flag.
 * @param mutexes Pointer to the mutexes structure containing
 * the term_flag mutex.
 */
void	set_termination_flag(bool *term_flag_ptr, t_mutexes *mutexes)
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
 * @param mutexes Pointer to the mutexes structure containing
 * the term_flag mutex.
 */
bool	termination_requested(bool *term_flag_ptr, t_mutexes *mutexes)
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
 * @param mutexes Pointer to the mutexes structure containing
 * the term_flag mutex.
 *
 * @return Always returns (void*)ERROR.
 */
void	*handle_thread_error(bool *term_flag_ptr, t_mutexes *mutexes)
{
	if (!term_flag_ptr || !mutexes)
	{
		error_msg("missing parameters", "handle_thread_error");
		return ((void *)ERROR);
	}
	set_termination_flag(term_flag_ptr, mutexes);
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

/**
 * @brief Retrieves protected data from a philosopher structure in a thread-safe
 *        manner.
 *
 * Depending on the requested data type, this function locks the appropriate
 * mutex, copies the value from the philosopher structure, and then unlocks the
 * mutex. It ensures that concurrent access to shared data is handled safely.
 *
 * @param data The type of data to retrieve (LAST_MEAL or MEALS_EATEN).
 * @param storage_ptr Pointer to where the retrieved value will be stored.
 * @param philo Pointer to the philosopher structure from which to read data.
 *
 * @return SUCCESS if the data was successfully retrieved, ERROR otherwise.
 *
 * @note The function returns ERROR if any pointer is NULL or if mutex
 *       operations fail.
 * @warning Only use with valid philosopher structures and initialized mutexes.
 */
t_error	get_protected_data(t_protected_data data, t_ms *storage_ptr,
		t_philo *philo)
{
	if (!storage_ptr || !philo)
	{
		error_msg("missing parameters", "handle_thread_error");
		return (ERROR);
	}
	if (data == LAST_MEAL)
	{
		if (w_mutex(LOCK, philo->mutexes->last_meal[philo->id]))
			return (ERROR);
		*storage_ptr = philo->last_meal;
		if (w_mutex(UNLOCK, philo->mutexes->last_meal[philo->id]))
			return (ERROR);
		return (SUCCESS);
	}
	else if (data == MEALS_EATEN)
	{
		if (w_mutex(LOCK, philo->mutexes->last_meal[philo->id]))
			return (ERROR);
		*storage_ptr = philo->meals_eaten;
		if (w_mutex(UNLOCK, philo->mutexes->last_meal[philo->id]))
			return (ERROR);
		return (SUCCESS);
	}
	return (ERROR);
}
