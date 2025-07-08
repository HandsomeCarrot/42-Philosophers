/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:46:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 12:59:18 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// is given philosopher dead?
// if dead print message and return TERMINATE
// if alive return SUCCESS and do nothing
static t_error	check_death(t_philo *philo)
{
	if (!philo)
	{
		error_msg("missing parameters", "check_death");
		return (ERROR);
	}
	// TODO
	return (SUCCESS);
}

// change function name
// check if current philo is full
// sets the boolean
static t_error	check_fullness(bool *all_full, t_philo *philo)
{
	t_ms	meals_eaten;

	if (!philo || !all_full)
	{
		error_msg("missing parameters", "check_fullness");
		return (ERROR);
	}
	if (w_mutex(LOCK, philo->mutexes->meals_eaten[philo->id]))
		return (ERROR);
	meals_eaten = philo->meals_eaten;
	if (w_mutex(UNLOCK, philo->mutexes->meals_eaten[philo->id]))
		return (ERROR);
	if (meals_eaten < philo->input->meal_limit)
		*all_full = false;
	return (SUCCESS);
}

// checks for given philo
// is it dead?
// if all before this one where full: is it full?
static t_error	check_philo(bool *all_full, t_philo *philo)
{
	t_error	error;

	if (!philo || !all_full)
	{
		error_msg("missing parameters", "check_philo");
		return (ERROR);
	}
	error = check_death(philo);
	if (error != SUCCESS)
		return (error);
	if (philo->input->has_meal_limit && *all_full)
	{
		if (check_fullness(all_full, philo) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

// docs
// check if monitor should terminate threads
// dead / all full
static t_error	check_all_philos(t_program *program)
{
	t_ms	philo_index;
	bool	all_full;
	t_error	error;

	if (!program)
	{
		error_msg("missing parameters", "check_all_philos");
		return (ERROR);
	}
	all_full = true;
	philo_index = 0;
	while (philo_index < program->philo_count)
	{
		error = check_philo(&all_full, &program->philos[philo_index]);
		if (error != SUCCESS)
			return (error);
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
