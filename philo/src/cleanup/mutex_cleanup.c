/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:13:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Safely destroys a single mutex.
 *
 * Attempts to destroy the given mutex and handles potential errors. Logs
 * appropriate error messages if the destruction fails.
 *
 * @param mutex Pointer to the mutex to be destroyed. Can be NULL.
 * @return t_error SUCCESS if mutex was destroyed or was NULL, ERROR if
 *         destruction failed (mutex was in use or other error occurred).
 */
static t_error	destroy_mutex(pthread_mutex_t *mutex)
{
	int	error;

	if (!mutex)
		return (SUCCESS);
	error = pthread_mutex_destroy(mutex);
	if (error == 0)
		return (SUCCESS);
	if (error == EBUSY)
		error_msg("failed to destroy mutex", "mutex is in use");
	else
		error_msg("failed to destroy mutex", NULL);
	return (ERROR);
}

/**
 * @brief Destroys an array of mutexes and frees the array memory.
 *
 * Iterates through the mutex array, destroying each mutex individually.
 * Frees the array memory after all mutexes are destroyed.
 *
 * @param count Number of mutexes in the array.
 * @param mutex_array Double pointer to the mutex array to be destroyed.
 * @return t_error SUCCESS if all mutexes were destroyed or array was NULL,
 *         ERROR if any mutex destruction failed.
 */
t_error	destroy_mutex_array(t_count count, pthread_mutex_t **mutex_array)
{
	t_count	index;

	if (!mutex_array || !*mutex_array)
		return (SUCCESS);
	index = 0;
	while (index < count)
	{
		if (destroy_mutex((*mutex_array) + index) != SUCCESS)
			return (ERROR);
		index++;
	}
	free(*mutex_array);
	return (SUCCESS);
}

/**
 * @brief Destroys all mutexes used in the philosopher simulation.
 *
 * Handles destruction of all mutex types in the simulation:
 * - Print mutex
 * - Termination mutex
 * - Start mutexes array
 * - Fork mutexes array
 * - Meal mutexes array
 * - Full mutexes array
 *
 * @param data Pointer to the simulation data structure containing all mutexes.
 * @return t_error SUCCESS if all mutexes were destroyed successfully,
 *         ERROR if any mutex destruction failed.
 */
t_error	destroy_all_mutexes(t_data *data)
{
	t_all_mutexes	mutexes;
	t_count			philo_count;
	t_error			error;

	mutexes = data->mutexes;
	philo_count = data->input.philo_count;
	error = destroy_mutex(&mutexes.print_mutex);
	if (destroy_mutex(&mutexes.term_mutex))
		error = ERROR;
	if (destroy_mutex_array((philo_count + 1), &mutexes.start_mutexes))
		error = ERROR;
	if (destroy_mutex_array(philo_count, &mutexes.fork_mutexes))
		error = ERROR;
	if (destroy_mutex_array(philo_count, &mutexes.meal_mutexes))
		error = ERROR;
	if (destroy_mutex_array(philo_count, &mutexes.full_mutexes))
		error = ERROR;
	return (error);
}
