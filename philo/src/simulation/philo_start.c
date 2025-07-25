/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:23:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 02:26:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Handles mutex operations for philosopher forks with error checking.
 *
 * Performs lock/unlock operations on fork mutexes with additional safety checks.
 * If termination is requested during locking, automatically unlocks and returns.
 * Also handles fork state printing when successfully locked.
 *
 * @param action The mutex operation to perform (LOCK/UNLOCK)
 * @param fork Pointer to the fork mutex to operate on
 * @param data Philosopher data structure containing termination flags
 * @return t_error SUCCESS on success, ERROR on mutex failure,
 *         TERMINATE if termination requested during lock
 */
static t_error	mutex_fork(t_mutex_action action, pthread_mutex_t *fork,
		t_philo *data)
{
	t_error	error;

	if (!fork || !data)
		return (error_msg("missing parameters", "mutex_fork"));
	if (w_mutex(action, fork))
		return (ERROR);
	if (action == UNLOCK)
		return (SUCCESS);
	if (termination_requested(data->term_flag, data->mutexes.term_flag))
	{
		w_mutex(UNLOCK, fork);
		return (TERMINATE);
	}
	error = print_state(FORK, NULL, data);
	if (error != SUCCESS)
		w_mutex(UNLOCK, fork);
	return (error);
}

/**
 * @brief Manages both forks for a philosopher with proper error handling.
 *
 * Coordinates locking/unlocking of both forks with proper rollback on failure.
 * Ensures forks are always properly released if acquisition fails.
 *
 * @param action The mutex operation to perform (LOCK/UNLOCK)
 * @param data Philosopher data structure containing fork mutexes
 * @return t_error SUCCESS on success, ERROR on mutex failure,
 *         TERMINATE if termination requested during lock
 */
t_error	philo_forks(t_mutex_action action, t_philo *data)
{
	t_error			error;

	error = mutex_fork(action, data->mutexes.first_fork, data);
	if (error != SUCCESS)
		return (error);
	error = mutex_fork(action, data->mutexes.second_fork, data);
	if (error != SUCCESS && action == LOCK)
		mutex_fork(UNLOCK, data->mutexes.first_fork, data);
	return (error);
}

/**
 * @brief Main philosopher routine loop.
 *
 * Handles the core philosopher cycle of eating, sleeping, and thinking.
 * Special case for single philosopher (just picks up fork). Otherwise
 * starts with initial thinking stage, then enters the main cycle until
 * an error occurs or termination is requested.
 *
 * @param data Philosopher data structure containing all necessary state
 * @return t_error SUCCESS on normal termination, ERROR on failure,
 *         TERMINATE if termination requested
 */
static t_error	philo_routine(t_philo *data)
{
	t_error	error;

	if (data->input->philo_count == 1)
		return (print_state(FORK, NULL, data));
	error = thread_sleep(data->initial_think_time, data);
	while (error == SUCCESS)
	{
		error = philo_eat(data);
		if (error == SUCCESS)
			error = philo_sleep(data);
		if (error == SUCCESS)
			error = philo_think(data);
	}
	return (error);
}

/**
 * @brief Entry point for philosopher thread.
 *
 * Initializes philosopher thread, waits for start signal, then begins routine.
 * Handles special cases for immediate termination and single philosopher.
 * Manages termination flag on critical errors.
 *
 * @param ptr Void pointer cast to t_philo* containing philosopher data
 * @return void* Cast t_error value: SUCCESS on normal termination,
 *         ERROR on failure, TERMINATE if termination requested
 */
void	*philo_start(void *ptr)
{
	t_philo	*data;
	t_error	error;

	if (!ptr)
		return ((void *)error_msg("missing parameters", "philo_start"));
	data = ptr;
	if (data->input->time_to_die == 0)
		return ((void *)TERMINATE);
	error = wait_for_start(data->mutexes.start);
	if (error != SUCCESS)
		return ((void *)error);
	if (termination_requested(data->term_flag, data->mutexes.term_flag))
		return ((void *)SUCCESS);
	error = philo_routine(data);
	if (error == ERROR)
		set_termination_flag(data->term_flag, data->mutexes.term_flag);
	return ((void *)error);
}
