/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:33:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief Main entry point for the Philosophers program.
 *
 * This function handles the initialization, execution, and cleanup of the
 * Philosophers simulation. It validates input arguments, initializes program
 * data, starts the simulation, and ensures proper cleanup of resources.
 *
 * @param argc The number of command line arguments.
 * @param argv Array of command line argument strings.
 *             Expected format:
 *             ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
 *             [number_of_times_each_philosopher_must_eat]
 *
 * @return Returns ERROR (1) if any operation fails, otherwise SUCCESS (0).
 *         Specific error cases include:
 *         - Incorrect number of arguments
 *         - Data initialization failure
 *         - Simulation startup failure
 *         - Cleanup failure
 *
 * @note The program requires between 4 and 5 arguments to run properly.
 * @warning Improper argument values may lead to undefined behavior.
 * @see initialize_data(), start_simulation(), erase_data()
 */

int	main(int argc, char **argv)
{
	t_data	*data;
	t_error	error;

	if (argc < 5 || argc > 6)
		return (error_msg("Incorrect input", "wrong amount of arguments"));
	data = NULL;
	error = initialize_data(argc, argv, &data);
	if (!error && start_simulation(data) != SUCCESS)
	{
		error = ERROR;
		set_termination_flag(&data->term_flag, &data->mutexes.term_mutex);
	}
	if (erase_data(data) != SUCCESS)
		error = ERROR;
	return (error);
}
