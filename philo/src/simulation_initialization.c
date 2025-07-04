/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:57:12 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 16:19:20 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
t_error	all_forks(t_mutex_action action, t_program *program)
{
	pthread_mutex_t	**forks;
	t_ms			fork_index;
	t_ms			fork_count;

	if (!program)
	{
		error_msg("missing parameters", "all_forks");
		return (ERROR);
	}
	forks = program->mutexes.forks;
	fork_index = 0;
	fork_count = program->philo_count;
	while (fork_index < fork_count)
	{
		if (w_mutex(action, forks[fork_index]) != SUCCESS)
			return (ERROR);
		fork_index++;
	}
	return (SUCCESS);
}

/**
 * @brief Creates and initializes a philosopher thread with given ID.
 *
 * This function initializes a philosopher structure with the provided ID,
 * sets up its initial state (last meal time, meals eaten count), assigns
 * references to shared program resources (input parameters, mutexes, error
 * flag), and creates a new pthread to run the philosopher's routine.
 *
 * @param id The unique identifier for the philosopher to be created.
 * @param program Pointer to the main program structure containing all
 *                shared resources and philosopher array.
 *
 * @note This function will terminate the program if pthread creation fails.
 * @warning The function does not validate input parameters before use.
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
	program->philos[id].term_flag_ptr = &program->terminate_threads;
	if (pthread_create(&program->philos[id].thread, NULL, routine_start,
			&program->philos[id]))
	{
		error_msg("failed to create philo: ", mstoa(id));
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Starts the dining philosophers simulation by creating all threads.
 *
 * This function initializes the simulation start time, then creates all
 * philosopher threads by calling create_philo for each philosopher ID
 * from 0 to philo_count-1. The simulation start time is recorded before
 * creating any threads to ensure consistent timing across all philosophers.
 *
 * @param program Pointer to the main program structure containing
 *                simulation parameters and philosopher data.
 *
 * @note The function will terminate the program if program pointer is NULL
 *       or if getting the start time fails.
 * @see create_philo()
 */
t_error	start_simulation(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;

	if (!program)
	{
		error_msg("missing parameters", "start_simulation");
		return (ERROR);
	}
	philo_index = 0;
	philo_count = program->philo_count;
	if (all_forks(LOCK, program) != SUCCESS)
		return (all_forks(UNLOCK, program), ERROR);
	while (philo_index < philo_count)
	{
		if (create_philo(philo_index, program) != SUCCESS)
			return (all_forks(UNLOCK, program), ERROR);
		philo_index++;
	}
	if (get_time_in_ms(&program->input.sim_start_time, &program->mutexes))
		return (all_forks(UNLOCK, program), ERROR);
	if (all_forks(UNLOCK, program) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
