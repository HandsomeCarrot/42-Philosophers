/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:33:27 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 15:16:47 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
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

// docs
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

// docs
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
		philo_index++;
	}
	if (create_thread(&data->threads.monitor, &monitor_start, &data->monitor,
			data))
		return (error_msg("failed to create thread", NULL));
	return (SUCCESS);
}

// docs
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
