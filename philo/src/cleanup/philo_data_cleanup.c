/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:36:31 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:15:02 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Frees all dynamically allocated memory in the philosopher data structure.
 *
 * This function safely deallocates memory for the philosopher-related data
 * structures including last meal times, fullness trackers, and philosopher data.
 * It checks each pointer before freeing to avoid double-free errors.
 *
 * @param data Pointer to the main data structure containing philosopher data.
 * @return SUCCESS on successful cleanup, or appropriate error code if any
 *         issues occur during cleanup (though current implementation always
 *         returns SUCCESS).
 * @note This function is part of the cleanup process and should be called
 *       when the simulation is complete or when initialization fails.
 * @warning The function assumes the data structure was properly initialized.
 *          Calling with uninitialized or partially initialized data may lead
 *          to undefined behavior.
 */

t_error	free_philo_data(t_data *data)
{
	if (data->philos.last_meals)
		free(data->philos.last_meals);
	if (data->philos.philo_full)
		free(data->philos.philo_full);
	if (data->philos.philo_data)
		free(data->philos.philo_data);
	return (SUCCESS);
}
