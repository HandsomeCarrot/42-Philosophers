/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:28:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:23:09 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Initializes a single mutex with default attributes.
 *
 * This function initializes a pthread mutex with NULL attributes. It performs
 * error checking and returns appropriate status codes. On failure, it logs
 * error messages indicating the reason for failure.
 *
 * @param mutex Pointer to the mutex to be initialized. Must not be NULL.
 * @return SUCCESS if initialization succeeds, ERROR otherwise.
 * @note This is a static helper function only used within this file.
 * @warning Passing a NULL mutex pointer will result in an error.
 */
static t_error	init_mutex(pthread_mutex_t *mutex)
{
	int	error;

	if (!mutex)
		return (error_msg("missing parameters", "init_mutex"));
	error = pthread_mutex_init(mutex, NULL);
	if (error == 0)
		return (SUCCESS);
	else if (error == ENOMEM)
		error_msg("failed to initialize mutex", "out of memory");
	else
		error_msg("failed to initialize mutex", NULL);
	return (ERROR);
}

/**
 * @brief Creates and initializes an array of mutexes with tracking.
 *
 * Allocates memory for an array of mutexes and a corresponding tracking array.
 * Initializes each mutex and marks successful initialization in the tracking array.
 * If any mutex initialization fails, it cleans up all previously initialized 
 * mutexes in the array before returning NULL.
 *
 * @param array_size Number of mutexes to create in the array.
 * @param init_tracker Double pointer to store the tracking array.
 * @return Pointer to the array of initialized mutexes on success, NULL on
 *         failure.
 * @note Uses w_calloc for allocation which zeroes out the memory.
 * @warning If initialization fails partway through, all previously initialized
 *          mutexes in the array will be properly destroyed.
 */
static pthread_mutex_t	*new_mutex_array(t_count array_size, bool **init_tracker)
{
	pthread_mutex_t	*mutexes;
	bool			*tracker;
	t_count			index;

	mutexes = w_calloc(array_size, sizeof(pthread_mutex_t));
	if (!mutexes)
		return (NULL);
	tracker = w_calloc(array_size, sizeof(bool));
	if (!tracker)
	{
		free(mutexes);
		return (NULL);
	}
	*init_tracker = tracker;
	index = 0;
	while (index < array_size)
	{
		if (init_mutex(mutexes + index) != SUCCESS)
		{
			destroy_mutex_array(index, &mutexes, &tracker);
			*init_tracker = NULL;
			return (NULL);
		}
		tracker[index] = true;
		index++;
	}
	return (mutexes);
}

/**
 * @brief Initializes all mutexes required for the philosopher simulation.
 *
 * Creates and initializes all mutexes needed for the simulation including:
 * - Print mutex for synchronized output
 * - Termination mutex for program termination control
 * - Start mutexes (one per philosopher plus one extra)
 * - Fork mutexes (one per philosopher)
 * - Meal mutexes (one per philosopher)
 * - Full mutexes (one per philosopher)
 * 
 * Also initializes tracking arrays to record successful initialization.
 *
 * @param data Pointer to the main program data structure containing mutex
 *             references and philosopher count.
 * @return SUCCESS if all mutexes are initialized successfully, ERROR if any
 *         initialization fails.
 * @note If any mutex initialization fails, all previously initialized mutexes
 *       will be properly cleaned up.
 * @warning This function must be called before starting any philosopher threads.
 */
t_error	create_mutexes(t_data *data)
{
	t_all_mutexes	*mutexes;
	t_count			philo_count;

	mutexes = &data->mutexes;
	philo_count = data->input.philo_count;
	mutexes->print_mutex_init = false;
	mutexes->term_mutex_init = false;
	if (init_mutex(&mutexes->print_mutex) != SUCCESS)
		return (ERROR);
	mutexes->print_mutex_init = true;
	if (init_mutex(&mutexes->term_mutex) != SUCCESS)
		return (ERROR);
	mutexes->term_mutex_init = true;
	mutexes->start_mutexes = new_mutex_array(philo_count + 1,
			&mutexes->start_mutexes_init);
	if (!mutexes->start_mutexes)
		return (ERROR);
	mutexes->fork_mutexes = new_mutex_array(philo_count,
			&mutexes->fork_mutexes_init);
	if (!mutexes->fork_mutexes)
		return (ERROR);
	mutexes->meal_mutexes = new_mutex_array(philo_count,
			&mutexes->meal_mutexes_init);
	if (!mutexes->meal_mutexes)
		return (ERROR);
	mutexes->full_mutexes = new_mutex_array(philo_count,
			&mutexes->full_mutexes_init);
	if (!mutexes->full_mutexes)
		return (ERROR);
	return (SUCCESS);
}
