/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 19:18:02 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Destroys and frees a pthread mutex.
 *
 * This function safely destroys a mutex using pthread_mutex_destroy and
 * then frees the memory allocated for the mutex. If the mutex destruction
 * fails, an error message is logged but the memory is still freed.
 *
 * @param mutex Pointer to the pthread_mutex_t to be destroyed and freed.
 *
 * @note The mutex should be in an unlocked state before calling this
 *       function to avoid undefined behavior.
 * @warning If pthread_mutex_destroy fails, an error is logged but the
 *          function continues to free the memory, which may lead to
 *          resource leaks in the system.
 */
static t_error	destroy_mutex(pthread_mutex_t *mutex)
{
	t_error	error;

	error = SUCCESS;
	if (!mutex)
	{
		error_msg("missing parameters", "free_mutex");
		return (ERROR);
	}
	error = pthread_mutex_destroy(mutex);
	free(mutex);
	if (error != SUCCESS)
		error_msg("failed to destroy mutex", NULL);
	return (error);
}

// docs
static t_error	destroy_forks(t_program *program)
{
	t_ms	fork_index;
	t_ms	fork_count;
	t_error	error;

	if (!program || !program->mutexes.forks)
	{
		error_msg("missing parameters", "clean_forks");
		return (ERROR);
	}
	error = SUCCESS;
	fork_index = 0;
	fork_count = program->philo_count;
	while (fork_index < fork_count && program->mutexes.forks[fork_index])
	{
		if (destroy_mutex(program->mutexes.forks[fork_index]) != SUCCESS)
			error = ERROR;
		fork_index++;
	}
	free(program->mutexes.forks);
	return (error);
}

/**
 * @brief Cleans up all mutexes allocated in the program structure.
 *
 * This function systematically destroys and frees all mutexes used in
 * the philosophers program, including the stop mutex, print mutex, and
 * all fork mutexes. It handles null pointer checks to prevent crashes
 * during cleanup.
 *
 * @param program Pointer to the main program structure containing all
 *                mutexes to be cleaned up.
 *
 * @note This function performs null pointer checks before attempting to
 *       clean up any mutex resources.
 * @warning The fork cleanup loop condition checks both the index bound
 *          and null pointer, which may cause issues if the array is not
 *          properly null-terminated.
 */
t_error	destroy_all_mutexes(t_program *program)
{
	t_error	error;

	if (!program)
	{
		error_msg("missing parameters", "clean_mutexes");
		return (ERROR);
	}
	error = SUCCESS;
	if (destroy_mutex(program->mutexes.stop) != SUCCESS)
		error = ERROR;
	if (destroy_mutex(program->mutexes.print) != SUCCESS)
		error = ERROR;
	if (destroy_forks(program) != SUCCESS)
		error = ERROR;
	return (error);
}
