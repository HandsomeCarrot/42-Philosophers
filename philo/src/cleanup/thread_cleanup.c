/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 16:24:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Joins a single thread and checks for errors.
 *
 * Waits for the specified thread to finish execution. If the thread returns
 * an error or pthread_join fails, the program's termination flag is set.
 *
 * @param thread The pthread_t to join.
 * @param program Pointer to the main program structure for error handling.
 *
 * @return SUCCESS if the thread was joined successfully, ERROR otherwise.
 *
 * @note If thread returns (void*)ERROR, the termination flag is set.
 */
static t_error	join_thread(pthread_t thread, t_program *program)
{
	void	*thread_error;

	if (!program)
	{
		error_msg("missing parameters", "join_thread");
		return (ERROR);
	}
	thread_error = NULL;
	if (pthread_join(thread, &thread_error))
	{
		set_termination_flag(&program->term_flag, &program->mutexes);
		error_msg("failed to join a thread", NULL);
		return (ERROR);
	}
	if (thread_error && thread_error == (void *)ERROR)
	{
		set_termination_flag(&program->term_flag, &program->mutexes);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Joins all philosopher and monitor threads.
 *
 * Iterates through all philosopher threads and the monitor thread, joining
 * each one to ensure clean program termination.
 *
 * @param program Pointer to the main program structure containing threads.
 *
 * @return SUCCESS if all threads were joined, ERROR otherwise.
 *
 * @note Continues joining remaining threads even if one join fails.
 * @warning If program or program->philos is NULL, ERROR is returned.
 */
t_error	join_all_threads(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;
	t_error	error;

	if (!program || !program->philos)
	{
		error_msg("missing parameters", "join_all_threads");
		return (ERROR);
	}
	error = SUCCESS;
	philo_index = 0;
	philo_count = program->philo_count;
	while (philo_index < philo_count)
	{
		if (join_thread(program->philos[philo_index].thread, program))
			error = ERROR;
		philo_index++;
	}
	if (join_thread(program->monitor_thread, program))
		error = ERROR;
	return (error);
}
