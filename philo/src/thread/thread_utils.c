/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:40:08 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/02 18:35:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Gets the current time in milliseconds since Unix epoch.
 *
 * This function retrieves the current system time using gettimeofday()
 * and converts it to milliseconds since the Unix epoch. The result is
 * stored in the provided pointer. If an error occurs during time
 * retrieval, an error message is displayed with proper mutex protection
 * for thread safety.
 *
 * @param ms_ptr Pointer to a t_ms variable where the current time in
 *               milliseconds will be stored. Must not be NULL.
 * @param mutex Pointer to a mutex used for thread-safe error message
 *              output. Can be NULL if thread safety is not required.
 *
 * @return SUCCESS (0) if the time was successfully retrieved and stored,
 *         ERROR (1) if ms_ptr is NULL or gettimeofday() fails.
 *
 * @note This function is thread-safe when a valid mutex is provided.
 */
int	get_time_in_ms(t_ms *ms_ptr, t_mutexes *mutexes)
{
	struct timeval	tv;
	t_ms			current_time;

	if (!ms_ptr)
		return (ERROR);
	if (gettimeofday(&tv, NULL) != SUCCESS && mutexes)
	{
		w_mutex(LOCK, mutexes->print);
		error_msg("failed to get time", NULL);
		w_mutex(UNLOCK, mutexes->print);
		return (ERROR);
	}
	current_time = (t_ms)(tv.tv_sec * 1000);
	current_time += (t_ms)(tv.tv_usec / 1000);
	*ms_ptr = current_time;
	return (SUCCESS);
}

/**
 * @brief Sets an error flag in a thread-safe manner.
 *
 * This function atomically updates the error flag by acquiring the stop
 * mutex lock before writing to the error flag variable. It performs
 * parameter validation to ensure all required pointers are valid before
 * proceeding with the operation.
 *
 * @param error The error code of type t_error to be set in the flag.
 * @param error_flag A pointer to the integer error flag to be updated.
 * @param mutexes A pointer to the mutexes structure containing the stop
 *                mutex used for thread synchronization.
 *
 * @note This function is thread-safe and uses mutex locking to prevent
 *       race conditions when multiple threads access the error flag.
 * @warning If any of the input parameters are NULL, the function returns
 *          early without performing any operation.
 */
void	set_error_flag(t_error error, int *error_flag, t_mutexes *mutexes)
{
	if (!mutexes || !error_flag || !mutexes)
		return ;
	w_mutex(LOCK, mutexes->stop);
	*error_flag = error;
	w_mutex(UNLOCK, mutexes->stop);
}

/**
 * @brief Retrieves the current error flag value in a thread-safe manner.
 *
 * This function atomically reads the error flag by acquiring the stop
 * mutex lock before accessing the error flag variable. The function
 * performs parameter validation to ensure all required pointers are
 * valid before attempting to read the error state.
 *
 * @param error_flag A pointer to the integer error flag to be read.
 * @param mutexes A pointer to the mutexes structure containing the stop
 *                mutex used for thread synchronization.
 *
 * @return int -> returns the value saved in the 'int error' variable
 * 				  in the main struct. Is used to tell if a thread 
 * 				  should terminate.
 * @note This function is thread-safe and uses mutex locking to ensure
 *       consistent reads of the error flag across multiple threads.
 * @warning If any of the input parameters are NULL, the function returns
 *          early without performing any operation. The function does not
 *          return the error value; it only reads it internally.
 */
int	get_error_flag(int *error_flag_ptr, t_mutexes *mutexes)
{
	int	error_flag;

	if (!error_flag_ptr || !mutexes)
		return (ERROR);
	w_mutex(LOCK, mutexes->stop);
	error_flag = *error_flag_ptr;
	w_mutex(UNLOCK, mutexes->stop);
	return (error_flag);
}
