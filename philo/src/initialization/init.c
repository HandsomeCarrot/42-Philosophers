/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:23:07 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/22 17:31:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Initialize all data structures and validate input parameters
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @param data_ptr Pointer to main data structure pointer
 * @return SUCCESS on success, ERROR on failure
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
	return (SUCCESS);
}
