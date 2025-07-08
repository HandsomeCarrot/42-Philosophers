/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 12:44:50 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Destroys and frees a pthread mutex.
 *
 * This function safely destroys a mutex using pthread_mutex_destroy and then
 * frees the memory allocated for the mutex. If the mutex destruction fails,
 * an error message is logged but the memory is still freed.
 *
 * @param mutex Pointer to the pthread_mutex_t to be destroyed and freed.
 *
 * @return SUCCESS if the mutex was destroyed, ERROR otherwise.
 *
 * @note The mutex should be unlocked before calling this function.
 * @warning If pthread_mutex_destroy fails, an error is logged but memory is
 *          still freed, which may lead to resource leaks.
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

/**
 * @brief Destroys and frees all fork mutexes in the program.
 *
 * Iterates through the array of fork mutexes, destroying and freeing each one.
 * Also frees the array itself.
 *
 * @param program Pointer to the main program structure containing fork mutexes.
 *
 * @return SUCCESS if all mutexes were destroyed, ERROR otherwise.
 *
 * @note The function checks for NULL pointers before proceeding.
 */
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
 * @brief Destroys all mutexes used in the philosophers program.
 *
 * Destroys and frees the term_flag mutex, print mutex, and all fork mutexes in the
 * program structure.
 *
 * @param program Pointer to the main program structure containing mutexes.
 *
 * @return SUCCESS if all mutexes were destroyed, ERROR otherwise.
 *
 * @note The function checks for NULL pointers before proceeding.
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
	if (destroy_mutex(program->mutexes.term_flag) != SUCCESS)
		error = ERROR;
	if (destroy_mutex(program->mutexes.print) != SUCCESS)
		error = ERROR;
	if (destroy_forks(program) != SUCCESS)
		error = ERROR;
	return (error);
}
