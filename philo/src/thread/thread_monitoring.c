/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:46:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 22:41:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
// change function name
// check if current philo is full
// sets the boolean
static t_error	current_philo_full(bool *all_full, t_philo *philo)
{
	if (!philo || !all_full)
		return (error_msg("missing parameters", "current_philo_full"), ERROR);
	// TODO
	return (SUCCESS);
}

// docs
// check if monitor should terminate threads
// dead / all full
static t_error	check_all_philos(t_program *program)
{
	t_ms	philo_index;
	bool	all_full;

	if (!program)
		return (error_msg("missing parameters", "check_all_philos"), ERROR);
	philo_index = 0;
	all_full = true;
	while (philo_index < program->philo_count)
	{
		// 	dead? print message
		if (all_full)
		{
			if (current_philo_full(&all_full, &program->philos[philo_index]))
				return (ERROR);
		}
		philo_index++;
	}
	if (all_full)
		return (TERMINATE);
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
	t_error		error;

	if (!data)
	{
		error_msg("missing parameters", "monitor_start");
		return ((void *)ERROR);
	}
	program = (t_program *)data;
	if (wait_for_start(program->mutexes.forks[0]))
		return (thread_error(&program->term_flag, &program->mutexes));
	error = SUCCESS;
	while (!is_termination_requested(&program->term_flag, &program->mutexes))
	{
		error = check_all_philos(program);
		if (error != SUCCESS)
		{
			terminate_threads(&program->term_flag, &program->mutexes);
			break ;
		}
		// wait a bit after all checks?
	}
	return ((void *)error);
}
