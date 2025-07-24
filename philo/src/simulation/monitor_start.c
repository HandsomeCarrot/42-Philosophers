/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:25:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 20:16:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static t_error	check_death(t_monitor *data)
{
	t_count	index;
	t_ms	elapsed_time;
	t_ms	time_since_last_meal;

	if (get_elapsed_time(&elapsed_time, data->input->sim_start_time) != SUCCESS)
		return (ERROR);
	index = 0;
	while (index < data->input->philo_count)
	{
		if (w_mutex(LOCK, &data->philos.meal_mutexes[index]) != SUCCESS)
			return (ERROR);
		time_since_last_meal = elapsed_time - data->philos.last_meals[index];
		if (w_mutex(UNLOCK, &data->philos.meal_mutexes[index]) != SUCCESS)
			return (ERROR);
		if (time_since_last_meal >= data->input->time_to_die)
		{
			print_state(DEATH, NULL, &data->philos.philo_data[index]);
			set_termination_flag(data->term_flag, data->term_mutex);
			return (TERMINATE);
		}
		index++;
	}
	return (SUCCESS);
}

// docs
static t_error	check_all_full(t_monitor *data)
{
	t_count	index;
	t_count	full_count;

	if (!data->input->has_meal_limit)
		return (SUCCESS);
	full_count = 0;
	index = 0;
	while (index < data->input->philo_count)
	{
		if (w_mutex(LOCK, &data->philos.full_mutexes[index]) != SUCCESS)
			return (ERROR);
		if (data->philos.philo_full[index])
			full_count++;
		if (w_mutex(UNLOCK, &data->philos.full_mutexes[index]) != SUCCESS)
			return (ERROR);
		index++;
	}
	if (full_count == data->input->philo_count)
	{
		set_termination_flag(data->term_flag, data->term_mutex);
		return (TERMINATE);
	}
	return (SUCCESS);
}

// docs
static t_error	monitor_routine(t_monitor *data)
{
	t_error	error;

	while (!termination_requested(data->term_flag, data->term_mutex))
	{
		error = check_death(data);
		if (error != SUCCESS)
			return (error);
		error = check_all_full(data);
		if (error != SUCCESS)
			return (error);
		if (precise_sleep(1) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

// docs
void	*monitor_start(void *ptr)
{
	t_monitor	*data;
	t_error		error;

	if (!ptr)
		return ((void *)error_msg("missing parameters", "philo_start"));
	data = ptr;
	error = wait_for_start(data->start_mutex);
	if (error)
		return ((void *)error);
	error = monitor_routine(data);
	return ((void *)error);
}
