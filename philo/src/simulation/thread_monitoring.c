/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:46:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/13 12:42:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Checks if a philosopher has died based on time since last meal.
 *
 * Compares the elapsed time since the philosopher's last meal to the allowed
 * time to die. If the philosopher has exceeded this time, prints a death
 * message and returns TERMINATE. Otherwise, returns SUCCESS.
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @return TERMINATE if the philosopher has died, SUCCESS if alive,
 *         ERROR on failure.
 *
 * @note Returns ERROR if philo is NULL or on data retrieval failure.
 */
static t_error	check_death(t_philo *philo)
{
	t_ms	time_starved;
	t_ms	elapsed_time;
	t_ms	last_meal;

	if (!philo)
	{
		error_msg("missing parameters", "check_death");
		return (ERROR);
	}
	if (get_protected_data(LAST_MEAL, &last_meal, philo))
		return (ERROR);
	if (get_elapsed_time_ms(&elapsed_time, philo->input))
		return (ERROR);
	if (validate_timestamps(last_meal, elapsed_time))
		return (ERROR);
	time_starved = elapsed_time - last_meal;
	if (time_starved >= philo->input->time_to_die)
	{
		set_termination_flag(philo->term_flag_ptr, philo->mutexes.term_flag);
		if (print_philo_state(DEATH, elapsed_time, philo) == ERROR)
			return (ERROR);
		return (TERMINATE);
	}
	return (SUCCESS);
}

/**
 * @brief Checks if a philosopher has died based on time since last meal.
 *
 * Compares the elapsed time since the philosopher's last meal to the allowed
 * time to die. If the philosopher has exceeded this time, prints a death
 * message and returns TERMINATE. Otherwise, returns SUCCESS.
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @return TERMINATE if the philosopher has died, SUCCESS if alive,
 *         ERROR on failure.
 *
 * @note Returns ERROR if philo is NULL or on data retrieval failure.
 */
static t_error	check_fullness(bool *all_full, t_philo *philo)
{
	t_ms	meals_eaten;

	if (!philo || !all_full)
	{
		error_msg("missing parameters", "check_fullness");
		return (ERROR);
	}
	if (get_protected_data(MEALS_EATEN, &meals_eaten, philo))
		return (ERROR);
	if (meals_eaten < philo->input->meal_limit)
		*all_full = false;
	return (SUCCESS);
}

/**
 * @brief Checks the status of a single philosopher for death or fullness.
 *
 * Calls check_death to determine if the philosopher has died. If a meal
 * limit is set and all_full is true, checks if the philosopher is full.
 *
 * @param all_full Pointer to a boolean tracking if all philosophers are full.
 * @param philo Pointer to the philosopher structure.
 *
 * @return SUCCESS if the philosopher is alive and checks pass,
 *         TERMINATE if dead or full, ERROR on failure.
 *
 * @note Returns ERROR if philo or all_full is NULL.
 */
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
	if (*all_full)
	{
		if (check_fullness(all_full, philo) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Checks all philosophers for death or completion.
 *
 * Iterates through all philosophers, checking each for death and fullness.
 * If any philosopher is dead, returns TERMINATE. If all are full, returns
 * TERMINATE.
 *
 * @param program Pointer to the main program structure.
 *
 * @return TERMINATE if any philosopher is dead or all are full,
 *         SUCCESS otherwise, ERROR on failure.
 *
 * @note Returns ERROR if program is NULL.
 */
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
	all_full = program->input.has_meal_limit;
	philo_index = 0;
	while (philo_index < program->input.philo_count)
	{
		error = check_philo(&all_full, &program->philos[philo_index]);
		if (error != SUCCESS)
			return (error);
		philo_index++;
	}
	if (all_full)
	{
		set_termination_flag(&program->term_flag, program->mutexes.term_flag);
		return (TERMINATE);
	}
	return (SUCCESS);
}

/**
 * @brief Entry point for the monitor thread.
 *
 * Waits for the simulation to start, then continuously monitors all
 * philosophers for death or completion. Sets the termination flag and
 * exits if a termination condition is met.
 *
 * @param data Pointer to the main program structure.
 *
 * @return Pointer to SUCCESS on normal completion, or ERROR on failure.
 *
 * @note Returns (void*)ERROR if data is NULL or on error.
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
	if (wait_for_start(program->mutexes.start_mutexes[0]))
		return (handle_thread_error(&program->term_flag, program->mutexes.term_flag));
	error = SUCCESS;
	while (!termination_requested(&program->term_flag, program->mutexes.term_flag))
	{
		error = check_all_philos(program);
		if (error != SUCCESS)
		{
			set_termination_flag(&program->term_flag, program->mutexes.term_flag);
			break ;
		}
	}
	return ((void *)error);
}
