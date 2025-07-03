/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:57:12 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/03 22:09:23 by vpoka            ###   ########.fr       */
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
		return (ERR_ALLOC);
	forks = program->mutexes.forks;
	fork_index = 0;
	fork_count = program->philo_count;
	while (fork_index < fork_count)
	{
		w_mutex(action, forks[fork_index]);
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
	program->philos[id].id = id;
	program->philos[id].last_meal = 0;
	program->philos[id].meals_eaten = 0;
	program->philos[id].input = &program->input;
	program->philos[id].mutexes = &program->mutexes;
	program->philos[id].error_flag_ptr = &program->error_flag;
	if (pthread_create(&program->philos[id].thread, NULL, routine_start,
			&program->philos[id]))
	{
		set_error_flag(ERR_THREAD, &program->error_flag, &program->mutexes);
		w_mutex(LOCK, program->mutexes.print);
		error_msg("failed to create philo: ", mstoa(id));
		w_mutex(UNLOCK, program->mutexes.print);
		return (ERR_THREAD);
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
	t_error	err;

	if (!program)
		return (ERR_SYNC);
	philo_index = 0;
	philo_count = program->philo_count;
	err = all_forks(LOCK, program);
	if (err != SUCCESS)
		return (err);
	while (philo_index < philo_count)
	{
		err = create_philo(philo_index, program);
		if (err != SUCCESS)
			break;
		philo_index++;
	}
	if (get_time_in_ms(&program->input.sim_start_time, &program->mutexes) != 0)
		return (ERR_TIME);
	err = all_forks(UNLOCK, program);
	if (err != SUCCESS)
		return (err);
	return (SUCCESS);
}
