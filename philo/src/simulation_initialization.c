/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:57:12 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/02 14:08:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
static void	create_philo(t_ms id, t_program *program)
{
	program->philos[id].id = id;
	get_time_in_ms(&program->philos[id].last_meal, &program->mutexes);
	program->philos[id].meals_eaten = 0;
	program->philos[id].input = &program->input;
	program->philos[id].mutexes = &program->mutexes;
	program->philos[id].global_error = &program->error;
	if (pthread_create(&program->philos[id].thread, NULL, routine_start,
			&program->philos[id]))
	{
		set_error(ERROR, &program->error, &program->mutexes);
		w_mutex(LOCK, program->mutexes.print);
		error_msg("failed to create philo: ", mstoa(id));
		w_mutex(UNLOCK, program->mutexes.print);
		exit_philo(ERROR, program);
	}
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
void	start_simulation(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;

	if (!program)
		exit_philo(ERROR, program);
	philo_index = 0;
	philo_count = program->philo_count;
	if (get_time_in_ms(&program->input.sim_start_time, &program->mutexes))
		exit_philo(ERROR, program);
	while (philo_index < philo_count)
	{
		create_philo(philo_index, program);
		philo_index++;
	}
}
