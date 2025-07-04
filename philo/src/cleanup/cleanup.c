/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 19:18:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		error = join_all_threads(program);
		free(program->philos);
	}
	if (destroy_all_mutexes(program) != SUCCESS)
		error = ERROR;
	free(program);
	return (error);
}
