/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 17:29:43 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
void	set_error(t_error error, int *error_flag, t_mutexes *mutexes)
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
int	get_error(int *error_flag, t_mutexes *mutexes)
{
	int	error;

	if (!error_flag || !mutexes)
		return ;
	w_mutex(LOCK, mutexes->stop);
	error = *error_flag;
	w_mutex(UNLOCK, mutexes->stop);
	return (error);
}

// docs
// TODO
void	*routine_start(void *data)
{
	t_philo	*philo;

	philo = data;
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %lu\n", philo->id);
	w_mutex(UNLOCK, philo->mutexes->print);
	return (NULL);
}
