/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/09 17:29:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Cleans up all resources and exits the philosophers program.
 *
 * This function ensures all dynamically allocated resources, threads, and
 * mutexes are properly cleaned up before the program terminates. It can also
 * set the termination flag for threads if requested.
 *
 * @param set_term_flag Boolean indicating whether to set the thread
 *                      termination flag before cleanup.
 * @param program Pointer to the main program structure containing all
 *                resources to be cleaned up.
 *
 * @return SUCCESS if cleanup was successful, ERROR otherwise.
 *
 * @note If program is NULL, cleanup is skipped and ERROR is returned.
 * @warning Freeing resources after partial initialization may lead to
 *          undefined behavior if not all pointers are valid.
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
		set_termination_flag(&program->term_flag, &program->mutexes);
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
