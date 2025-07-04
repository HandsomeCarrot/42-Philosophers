/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 19:04:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdint.h>

// docs
static t_error	join_philo(t_ms philo_index, t_program *program)
{
	void	*thread_return;

	if (!program)
	{
		error_msg("missing parameters", "join_philo");
		return (ERROR);
	}
	thread_return = NULL;
	if (pthread_join(program->philos[philo_index].thread, &thread_return))
	{
		terminate_threads(&program->terminate_threads, &program->mutexes);
		error_msg("failed to join thread: ", mstoa(philo_index));
		return (ERROR);
	}
	if (thread_return && (intptr_t)thread_return != SUCCESS)
	{
		terminate_threads(&program->terminate_threads, &program->mutexes);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Joins all philosopher threads to ensure clean termination.
 *
 * This function iterates through all philosopher threads in the program
 * and waits for each thread to complete execution using pthread_join.
 * If any thread join operation fails, an error is set and logged.
 *
 * @param program Pointer to the main program structure containing the
 *                philosopher threads and program state information.
 *
 * @note This function performs null pointer checks on both program and
 *       program->philos before attempting to join threads.
 * @warning If pthread_join fails for any thread, the program error state
 *          is set but the function continues attempting to join remaining
 *          threads.
 */
static t_error	join_philos(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;
	t_error	error;

	if (!program || !program->philos)
	{
		error_msg("missing parameters", "join_philos");
		return (ERROR);
	}
	error = SUCCESS;
	philo_index = 0;
	philo_count = program->philo_count;
	while (philo_index < philo_count)
	{
		if (join_philo(philo_index, program) != SUCCESS)
			error = ERROR;
		philo_index++;
	}
	return (error);
}

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
static t_error	free_mutex(pthread_mutex_t *mutex)
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
static t_error	clean_forks(t_program *program)
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
		if (free_mutex(program->mutexes.forks[fork_index]) != SUCCESS)
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
static t_error	clean_mutexes(t_program *program)
{
	t_error	error;

	if (!program)
	{
		error_msg("missing parameters", "clean_mutexes");
		return (ERROR);
	}
	error = SUCCESS;
	if (free_mutex(program->mutexes.stop) != SUCCESS)
		error = ERROR;
	if (free_mutex(program->mutexes.print) != SUCCESS)
		error = ERROR;
	if (clean_forks(program) != SUCCESS)
		error = ERROR;
	return (error);
}

/**
 * @brief Exits the philosophers program with proper resource cleanup.
 *
 * This function serves as the main exit point for the philosophers
 * program, ensuring all resources are properly cleaned up before
 * terminating the process with the specified error code.
 *
 * @param error The error code to exit with, typically from t_error enum.
 * @param program Pointer to the main program structure containing all
 *                resources that need to be cleaned up before exit.
 *
 * @note If program is null, the function will still exit with the
 *       specified error code but skip cleanup operations.
 */
t_error	cleanup_program(bool set_term_flag, t_program *program)
{
	t_error	error;

	error = SUCCESS;
	if (!program)
	{
		error_msg("missing parameters", "cleanup_program");
		return (ERROR);
	}
	if (set_term_flag)
		terminate_threads(&program->terminate_threads, &program->mutexes);
	if (program->philos)
	{
		error = join_philos(program);
		free(program->philos);
	}
	if (clean_mutexes(program) != SUCCESS)
		error = ERROR;
	free(program);
	return (error);
}
