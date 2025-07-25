/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 19:19:34 by vpoka            ###   ########.fr       */
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
 * @brief Destroys an array of mutexes using tracking and frees memory.
 *
 * Iterates through the mutex array, destroying only mutexes marked as 
 * initialized in the tracking array. Frees both the mutex array and 
 * tracking array memory after destruction.
 *
 * @param count Number of mutexes in the array.
 * @param mutex_array Double pointer to the mutex array to be destroyed.
 * @param init_tracker Double pointer to the tracking array.
 * @return t_error SUCCESS if all initialized mutexes were destroyed or 
 *         arrays were NULL, ERROR if any mutex destruction failed.
 */
t_error	destroy_mutex_array(t_count count, pthread_mutex_t **mutex_array,
		bool **init_tracker)
{
	t_count	index;
	t_error	error;

	if (!mutex_array || !*mutex_array)
		return (SUCCESS);
	error = SUCCESS;
	if (init_tracker && *init_tracker)
	{
		index = 0;
		while (index < count)
		{
			if ((*init_tracker)[index])
			{
				if (destroy_mutex((*mutex_array) + index) != SUCCESS)
					error = ERROR;
			}
			index++;
		}
		free(*init_tracker);
		*init_tracker = NULL;
	}
	free(*mutex_array);
	*mutex_array = NULL;
	return (error);
}

/**
 * @brief Destroys all mutexes used in the philosopher simulation.
 *
 * Handles destruction of all mutex types in the simulation using 
 * tracking arrays:
 *
 * - Print mutex (if initialized)
 * - Termination mutex (if initialized)
 * - Start mutexes array (using tracking)
 * - Fork mutexes array (using tracking)
 * - Meal mutexes array (using tracking)
 * - Full mutexes array (using tracking)
 *
 * @param data Pointer to the simulation data structure containing all mutexes.
 * @return t_error SUCCESS if all initialized mutexes were destroyed 
 *         successfully, ERROR if any mutex destruction failed.
 */
t_error	destroy_all_mutexes(t_data *data)
{
	t_all_mutexes	*mutexes;
	t_count			philo_count;
	t_error			error;

	mutexes = &data->mutexes;
	philo_count = data->input.philo_count;
	error = SUCCESS;
	if (mutexes->print_mutex_init && destroy_mutex(&mutexes->print_mutex))
		error = ERROR;
	if (mutexes->term_mutex_init && destroy_mutex(&mutexes->term_mutex))
		error = ERROR;
	if (destroy_mutex_array((philo_count + 1), &mutexes->start_mutexes,
			&mutexes->start_mutexes_init) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(philo_count, &mutexes->fork_mutexes,
			&mutexes->fork_mutexes_init) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(philo_count, &mutexes->meal_mutexes,
			&mutexes->meal_mutexes_init) != SUCCESS)
		error = ERROR;
	if (destroy_mutex_array(philo_count, &mutexes->full_mutexes,
			&mutexes->full_mutexes_init) != SUCCESS)
		error = ERROR;
	return (error);
}
