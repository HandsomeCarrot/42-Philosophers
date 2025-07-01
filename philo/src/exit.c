/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 16:06:35 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
static void	join_philos(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;

	if (!program || !program->philos)
		return ;
	philo_index = 0;
	philo_count = program->philo_count;
	while (philo_index < philo_count)
	{
		if (pthread_join(program->philos[philo_index].thread, NULL))
		{
			set_error(ERROR, &program->error, &program->mutexes);
			error_msg("failed to join thread: ", mstoa(philo_index));
		}
		philo_index++;
	}
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
void	free_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		error_msg("failed to destroy mutex", NULL);
	free(mutex);
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
static void	clean_mutexes(t_program *program)
{
	t_ms	fork_index;
	t_ms	fork_count;

	if (!program)
		return ;
	if (program->mutexes.stop)
		free_mutex(program->mutexes.stop);
	if (program->mutexes.print)
		free_mutex(program->mutexes.print);
	if (!program->mutexes.forks)
		return ;
	fork_index = 0;
	fork_count = program->philo_count;
	while (fork_index < fork_count || program->mutexes.forks[fork_index])
	{
		free_mutex(program->mutexes.forks[fork_index]);
		fork_index++;
	}
	free(program->mutexes.forks);
}

/**
 * @brief Performs complete cleanup of program resources.
 *
 * This function orchestrates the cleanup of all program resources by
 * joining philosopher threads, freeing philosopher structures, cleaning
 * up mutexes, and finally freeing the main program structure itself.
 *
 * @param program Pointer to the main program structure to be cleaned up.
 *
 * @note This function handles the case where program->philos might be
 *       null, ensuring safe cleanup even in partially initialized states.
 */
static void	cleanup(t_program *program)
{
	if (program->philos)
	{
		join_philos(program);
		free(program->philos);
	}
	clean_mutexes(program);
	free(program);
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
void	exit_philo(t_error error, t_program *program)
{
	if (program)
		cleanup(program);
	exit(error);
}
