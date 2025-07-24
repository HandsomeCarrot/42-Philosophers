/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:25:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:17:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Checks if any philosopher has died from starvation.
 *
 * Iterates through all philosophers and checks if the time since their last meal
 * exceeds the time_to_die parameter. If a philosopher has died, sets the
 * termination flag and returns TERMINATE.
 *
 * @param data Pointer to monitor data structure containing philosopher info
 * @return t_error SUCCESS if no deaths, TERMINATE if death detected, ERROR on failure
 * @note Locks and unlocks meal mutexes for thread-safe access to last meal times
 */
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

/**
 * @brief Checks if all philosophers have eaten their required meals.
 *
 * If the simulation has a meal limit, checks if all philosophers have reached
 * their meal count. If all are full, sets termination flag.
 *
 * @param data Pointer to monitor data structure
 * @return t_error SUCCESS if not all full, TERMINATE if all full, ERROR on failure
 * @note Only runs if has_meal_limit is true in input parameters
 */
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

/**
 * @brief Main monitoring routine that checks philosopher states.
 *
 * Continuously checks for philosopher deaths and meal completion until
 * termination is requested. Runs in a loop with a small sleep interval.
 *
 * @param data Pointer to monitor data structure
 * @return t_error SUCCESS if terminated normally, ERROR on failure
 * @warning Uses precise_sleep(1) to avoid busy waiting
 */
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

/**
 * @brief Entry point for monitor thread.
 *
 * Initializes monitoring process after waiting for simulation start.
 * Runs the main monitoring routine until termination.
 *
 * @param ptr Void pointer that should be cast to t_monitor*
 * @return void* Returns NULL on success, error value on failure
 * @note If ptr is NULL, returns error message about missing parameters
 */
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
