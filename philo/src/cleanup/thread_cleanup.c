/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:11:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 15:14:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Join a single thread with error handling
 * @param thread Thread handle to join
 * @param data Main data structure for error handling
 * @return SUCCESS on success, ERROR on failure
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
 * @brief Join all philosopher threads
 * @param data Main data structure containing philosopher threads
 * @return SUCCESS on success, ERROR on failure
 */
static t_error	join_all_philos(t_data *data)
{
	t_ms	index;
	t_error	error;

	error = SUCCESS;
	index = 0;
	while (index < data->input.philo_count)
	{
		if (join_thread(data->threads.philos[index], data) != SUCCESS)
			error = ERROR;
		index++;
	}
	return (error);
}

/**
 * @brief Join all threads (philosophers and monitor)
 * @param data Main data structure containing all thread handles
 * @return SUCCESS on success, ERROR on failure
 */
t_error	join_all_threads(t_data *data)
{
	t_error	error;

	if (!data->threads.philos)
		return (SUCCESS);
	error = join_all_philos(data);
	free(data->threads.philos);
	if (join_thread(data->threads.monitor, data) != SUCCESS)
		error = ERROR;
	return (error);
}
