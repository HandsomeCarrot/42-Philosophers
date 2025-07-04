/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 19:16:05 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
// watch out
#include <stdint.h>

// docs
static t_error	join_single_thread(t_ms philo_index, t_program *program)
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
t_error	join_all_threads(t_program *program)
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
		if (join_single_thread(philo_index, program) != SUCCESS)
			error = ERROR;
		philo_index++;
	}
	return (error);
}
