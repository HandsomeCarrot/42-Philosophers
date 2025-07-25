/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 19:20:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Joins a single thread and handles potential errors.
 *
 * Attempts to join the specified thread and checks for errors during the
 * joining process. Sets termination flag if any errors occur.
 *
 * @param thread The thread to be joined.
 * @param data Pointer to the program's shared data structure.
 * @return SUCCESS if thread joined successfully, ERROR otherwise.
 */
static t_error	join_thread(pthread_t thread, t_data *data)
{
	void	*thread_error;

	thread_error = NULL;
	if (pthread_join(thread, &thread_error))
	{
		set_termination_flag(&data->term_flag, &data->mutexes.term_mutex);
		error_msg("failed to join a thread", NULL);
		return (ERROR);
	}
	if (thread_error == (void *)ERROR)
	{
		set_termination_flag(&data->term_flag, &data->mutexes.term_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Joins all philosopher threads that were successfully created.
 *
 * Iterates through all philosopher threads and attempts to join only those
 * marked as initialized in the tracking array. Continues joining even if 
 * some threads fail, but returns overall error status.
 *
 * @param data Pointer to the program's shared data structure.
 * @return SUCCESS if all initialized threads joined successfully,
 *         ERROR if any failed.
 */
static t_error	join_all_philos(t_data *data)
{
	t_ms	index;
	t_error	error;

	error = SUCCESS;
	index = 0;
	while (index < data->input.philo_count)
	{
		if (data->threads.philos_init[index])
		{
			if (join_thread(data->threads.philos[index], data) != SUCCESS)
				error = ERROR;
		}
		index++;
	}
	return (error);
}

/**
 * @brief Joins all threads (philosophers and monitor) and cleans up resources.
 *
 * First joins all successfully created philosopher threads, then frees their 
 * memory along with tracking arrays, and finally joins the monitor thread if 
 * it was created. Returns overall success status of all operations.
 *
 * @param data Pointer to the program's shared data structure.
 * @return SUCCESS if all initialized threads joined successfully,
 *         ERROR if any failed.
 * @note If no philosopher threads exist (philos array is NULL), returns SUCCESS.
 */
t_error	join_all_threads(t_data *data)
{
	t_error	error;

	if (!data->threads.philos)
		return (SUCCESS);
	error = join_all_philos(data);
	free(data->threads.philos);
	if (data->threads.philos_init)
		free(data->threads.philos_init);
	if (data->threads.monitor_init)
	{
		if (join_thread(data->threads.monitor, data) != SUCCESS)
			error = ERROR;
	}
	return (error);
}
