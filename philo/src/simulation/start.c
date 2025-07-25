/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:33:27 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 18:44:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Locks or unlocks all start mutexes in the simulation.
 *
 * Iterates through all start mutexes in the data structure and performs
 * the specified mutex action (LOCK or UNLOCK) on each one.
 *
 * @param action The mutex action to perform (LOCK or UNLOCK).
 * @param data Pointer to the simulation data structure containing mutexes.
 * @return SUCCESS if all operations succeed, ERROR if any operation fails.
 */
static t_error	start_mutexes(t_mutex_action action, t_data *data)
{
	pthread_mutex_t	*mutexes;
	t_count			mutex_index;
	t_count			mutex_count;

	mutexes = data->mutexes.start_mutexes;
	mutex_count = data->input.philo_count + 1;
	mutex_index = 0;
	while (mutex_index < mutex_count)
	{
		if (w_mutex(action, (mutexes + mutex_index)) != SUCCESS)
			return (ERROR);
		mutex_index++;
	}
	return (SUCCESS);
}

/**
 * @brief Creates a new thread with error handling.
 *
 * Wrapper for pthread_create that includes parameter validation and error
 * handling. Sets termination flag if thread creation fails.
 *
 * @param thread_ptr Pointer to store the created thread ID.
 * @param start Pointer to the thread start routine function.
 * @param thread_data Data to pass to the thread start routine.
 * @param data Pointer to simulation data structure for error handling.
 * @return SUCCESS if thread created successfully, ERROR otherwise.
 */
static t_error	create_thread(pthread_t *thread_ptr, void *start,
		void *thread_data, t_data *data)
{
	int	error;

	if (!thread_ptr || !start || !thread_data || !data)
		return (error_msg("missing parameters", "create_thread"));
	error = pthread_create(thread_ptr, NULL, start, thread_data);
	if (error == 0)
		return (SUCCESS);
	set_termination_flag(&data->term_flag, &data->mutexes.term_mutex);
	return (error_msg("failed to create thread", NULL));
}

/**
 * @brief Starts all philosopher and monitor threads.
 *
 * Creates threads for each philosopher and the monitor thread. Marks
 * successful thread creation in tracking arrays. Sets termination flag 
 * if any thread creation fails.
 *
 * @param data Pointer to simulation data structure.
 * @return SUCCESS if all threads created successfully, ERROR otherwise.
 */
static t_error	start_threads(t_data *data)
{
	t_count	philo_index;
	t_count	philo_count;

	philo_count = data->input.philo_count;
	philo_index = 0;
	while (philo_index < philo_count)
	{
		if (create_thread(&data->threads.philos[philo_index], &philo_start,
				&data->philos.philo_data[philo_index], data))
			return (ERROR);
		data->threads.philos_init[philo_index] = true;
		philo_index++;
	}
	if (create_thread(&data->threads.monitor, &monitor_start, &data->monitor,
			data))
		return (error_msg("failed to create thread", NULL));
	data->threads.monitor_init = true;
	return (SUCCESS);
}

/**
 * @brief Initializes and starts the dining philosophers simulation.
 *
 * Coordinates the startup sequence: locks start mutexes, creates threads,
 * records simulation start time, then unlocks start mutexes.
 *
 * @param data Pointer to simulation data structure.
 * @return SUCCESS if simulation started successfully, ERROR otherwise.
 * @note The start mutexes ensure all threads start simultaneously.
 */
t_error	start_simulation(t_data *data)
{
	t_error	error;

	error = start_mutexes(LOCK, data);
	if (!error)
		error = start_threads(data);
	if (!error)
		error = get_current_time_ms(&data->input.sim_start_time);
	if (start_mutexes(UNLOCK, data))
		return (ERROR);
	return (error);
}
