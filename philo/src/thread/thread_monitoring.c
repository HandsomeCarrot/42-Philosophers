/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:46:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 21:00:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
static t_error	check_sim_state(t_program *program)
{
	(void)program;
	// TODO
	return (SUCCESS);
}

/**
 * @brief Entry point for the monitor thread.
 *
 * Waits for the simulation to start, then monitors the state of all
 * philosopher threads, checking for death or completion conditions.
 *
 * @param data Pointer to the main program structure.
 *
 * @return Pointer to SUCCESS on normal completion, or ERROR on failure.
 *
 * @note The monitor loop runs until the termination flag is set.
 */
void	*monitor_start(void *data)
{
	t_program	*program;

	program = (t_program *)data;
	if (wait_for_start(program->mutexes.forks[0]))
		return (thread_error(&program->terminate_threads, &program->mutexes));
	while (!is_termination_requested(&program->terminate_threads, &program->mutexes))
	{
		// check each thread if
		// 	dead?
		// all threads full?
		// set? thread termination flag
		// wait a bit after all checks
		// loop until term flag is set
	}
	return ((void *)SUCCESS);
}
