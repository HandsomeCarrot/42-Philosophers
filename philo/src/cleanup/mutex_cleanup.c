/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/10 15:49:59 by vpoka            ###   ########.fr       */
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
		error_msg("missing parameters", "destroy_mutex");
		return (ERROR);
	}
	error = pthread_mutex_destroy(mutex);
	free(mutex);
	if (error != SUCCESS)
		error_msg("failed to destroy mutex", NULL);
	return (error);
}

/**
 * @brief Destroys and frees a mutex array.
 *
 * Iterates through the array of mutexes, destroying and freeing each one.
 * Also frees the array itself.
 *
 * @param program Pointer to the main program structure.
 * @param mutex_array_ptr Pointer to the mutex array to destroy.
 * @param count Number of mutexes in the array.
 *
 * @return SUCCESS if all mutexes were destroyed, ERROR otherwise.
 */
static t_error	destroy_mutex_array(t_program *program,
		pthread_mutex_t ***mutex_array_ptr, t_ms count)
{
	t_ms	index;
	t_error	error;

	if (!program || !mutex_array_ptr || !*mutex_array_ptr)
	{
		error_msg("missing parameters", "destroy_mutex_array");
		return (ERROR);
	}
	error = SUCCESS;
	index = 0;
	while (index < count && (*mutex_array_ptr)[index])
	{
		if (destroy_mutex((*mutex_array_ptr)[index]) != SUCCESS)
			error = ERROR;
		index++;
	}
	free(*mutex_array_ptr);
	*mutex_array_ptr = NULL;
	return (error);
}

/**
 * @brief Destroys all mutexes used in the philosophers program.
 *
 * Destroys and frees the term_flag mutex, print mutex, and all fork, last_meal,
 * and meals_eaten mutexes in the program structure.
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
		error_msg("missing parameters", "destroy_all_mutexes");
		return (ERROR);
	}
	error = SUCCESS;
	if (destroy_mutex(program->mutexes.term_flag) != SUCCESS)
		error = ERROR;
	if (destroy_mutex(program->mutexes.print) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(program, &program->mutexes.forks,
			program->input.philo_count) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(program, &program->mutexes.last_meal,
			program->input.philo_count) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(program, &program->mutexes.meals_eaten,
			program->input.philo_count) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(program, &program->mutexes.start_mutexes,
			program->input.philo_count) != SUCCESS)
		error = ERROR;
	return (error);
}
