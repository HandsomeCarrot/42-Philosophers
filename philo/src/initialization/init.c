/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:23:07 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:35:43 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Initializes the main philosopher simulation data structure.
 *
 * This function allocates and initializes the main data structure for the
 * philosopher simulation. It processes input arguments, creates necessary
 * mutexes, allocates memory for philosopher data, and sets up thread storage.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @param data_ptr Pointer to store the initialized t_data structure.
 * @return t_error Returns SUCCESS on initialization, ERROR on failure.
 * @note The function performs multiple allocation operations and may fail if
 *       memory allocation or mutex creation fails.
 * @warning The caller is responsible for proper cleanup of the data structure
 *          if initialization fails partially.
 * @see cleanup_data() for proper cleanup of initialized resources.
 */
t_error	initialize_data(int argc, char **argv, t_data **data_ptr)
{
	t_data	*data;

	if (!argv || !data_ptr)
		return (error_msg("missing parameters", "initialize_data"));
	data = w_calloc(1, sizeof(t_data));
	if (!data)
		return (ERROR);
	*data_ptr = data;
	if (proccess_input(argc == 6, argv, data) != SUCCESS)
		return (ERROR);
	if (create_mutexes(data) != SUCCESS)
		return (ERROR);
	if (create_philo_data(data) != SUCCESS)
		return (ERROR);
	assign_monitor_data(data);
	data->threads.philos = w_calloc(data->input.philo_count, sizeof(pthread_t));
	if (!data->threads.philos)
		return (ERROR);
	data->threads.philos_init = w_calloc(data->input.philo_count, sizeof(bool));
	if (!data->threads.philos_init)
		return (ERROR);
	data->threads.monitor_init = false;
	return (SUCCESS);
}
