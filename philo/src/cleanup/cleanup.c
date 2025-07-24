/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:50:37 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:18:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Cleans up and frees all philosopher simulation data structures.
 *
 * This function performs a comprehensive cleanup of the simulation data:
 * - Joins all philosopher threads
 * - Destroys all mutexes (forks, print, death check)
 * - Frees allocated philosopher data
 * - Finally frees the main data structure
 *
 * @param data Pointer to the main simulation data structure containing
 *             all threads, mutexes and philosopher data to be cleaned up.
 * @return t_error Returns SUCCESS if all cleanup operations completed
 *                 successfully, ERROR if any operation failed. Note that
 *                 the function will attempt all cleanup steps even if
 *                 some fail, but will return ERROR in such cases.
 * @note This function handles NULL input gracefully by returning SUCCESS.
 * @warning The data pointer becomes invalid after this function call
 *          and should not be used again.
 */
t_error	erase_data(t_data *data)
{
	t_error	error;

	if (!data)
		return (SUCCESS);
	error = join_all_threads(data);
	if (destroy_all_mutexes(data) != SUCCESS)
		error = ERROR;
	if (free_philo_data(data) != SUCCESS)
		error = ERROR;
	free(data);
	return (error);
}
