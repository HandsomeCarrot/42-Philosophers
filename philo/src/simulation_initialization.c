/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:57:12 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 21:11:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Creates and initializes a philosopher thread with a given ID.
 *
 * Initializes the philosopher structure, sets up references to shared
 * resources, and creates a new pthread for the philosopher's routine.
 *
 * @param id The unique identifier for the philosopher.
 * @param program Pointer to the main program structure.
 *
 * @return SUCCESS on success, ERROR otherwise.
 *
 * @note Terminates the program if pthread creation fails.
 * @warning Does not validate input parameters before use.
 */
static t_error	create_philo(t_ms id, t_program *program)
{
	if (!program)
	{
		error_msg("missing parameters", "create_philo");
		return (ERROR);
	}
	program->philos[id].id = id;
	program->philos[id].last_meal = 0;
	program->philos[id].meals_eaten = 0;
	program->philos[id].input = &program->input;
	program->philos[id].mutexes = &program->mutexes;
	program->philos[id].term_flag_ptr = &program->term_flag;
	if (pthread_create(&program->philos[id].thread, NULL, philo_start,
			&program->philos[id]))
	{
		terminate_threads(&program->term_flag, &program->mutexes);
		error_msg("failed to create philo: ", mstoa(id));
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Starts all philosopher threads.
 *
 * Iterates through all philosopher IDs, creating a thread for each.
 *
 * @param program Pointer to the main program structure.
 *
 * @return SUCCESS if all threads are created, ERROR otherwise.
 */
static t_error	start_all_philosophers(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;

	if (!program)
	{
		error_msg("missing parameters", "start_all_philosophers");
		return (ERROR);
	}
	philo_index = 0;
	philo_count = program->philo_count;
	while (philo_index < philo_count)
	{
		if (create_philo(philo_index, program) != SUCCESS)
			return (ERROR);
		philo_index++;
	}
	return (SUCCESS);
}

/**
 * @brief Starts the monitor thread.
 *
 * Creates a separate thread to monitor the state of the simulation.
 *
 * @param program Pointer to the main program structure.
 *
 * @return SUCCESS if the monitor thread is created, ERROR otherwise.
 */
static t_error	start_monitor_thread(t_program *program)
{
	if (!program)
	{
		error_msg("missing parameters", "start_monitor_thread");
		return (ERROR);
	}
	if (pthread_create(&program->monitor_thread, NULL, &monitor_start, program))
	{
		terminate_threads(&program->term_flag, &program->mutexes);
		error_msg("failed to create monitoring thread", NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Starts the dining philosophers simulation by creating all threads.
 *
 * Initializes the simulation start time, creates all philosopher threads,
 * and starts the monitor thread. Ensures consistent timing across all
 * philosophers.
 *
 * @param program Pointer to the main program structure.
 *
 * @return SUCCESS if simulation starts successfully, ERROR otherwise.
 *
 * @note Terminates the program if program pointer is NULL or time retrieval
 *       fails.
 * @see create_philo()
 */
t_error	start_simulation(t_program *program)
{
	t_error	error;

	if (!program)
	{
		error_msg("missing parameters", "start_simulation");
		return (ERROR);
	}
	error = SUCCESS;
	if (all_forks(LOCK, program))
		error = ERROR;
	if (!error && start_all_philosophers(program))
		error = ERROR;
	if (!error && start_monitor_thread(program))
		error = ERROR;
	if (!error && get_time_in_ms(&program->input.sim_start_time,
			&program->mutexes))
		error = ERROR;
	if (all_forks(UNLOCK, program))
		return (ERROR);
	return (error);
}
