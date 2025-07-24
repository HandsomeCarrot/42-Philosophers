/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 16:18:42 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Destroy a single mutex with error handling
 * @param mutex Pointer to mutex to destroy
 * @return SUCCESS on success, ERROR on failure
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
 * @brief Destroy array of mutexes and free the array
 * @param count Number of mutexes in the array
 * @param mutex_array Pointer to array of mutexes to destroy
 * @return SUCCESS on success, ERROR on failure
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
 * @brief Destroy all mutexes in the main data structure
 * @param data Main data structure containing all mutexes
 * @return SUCCESS on success, ERROR on failure
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
