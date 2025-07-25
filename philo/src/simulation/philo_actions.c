/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:32:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 15:19:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Updates the philosopher's last meal timestamp
 *
 * Safely updates the last_meal timestamp in the philosopher's data structure
 * using mutex protection to prevent race conditions.
 *
 * @param timestamp The current timestamp to set as last meal time
 * @param data Pointer to the philosopher's data structure
 * @return t_error SUCCESS on success, ERROR on mutex failure
 */
static t_error	set_last_meal(t_ms timestamp, t_philo *data)
{
	pthread_mutex_t	*mutex;

	mutex = data->mutexes.meal;
	if (w_mutex(LOCK, mutex))
		return (ERROR);
	*data->last_meal = timestamp;
	if (w_mutex(UNLOCK, mutex))
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Increments the philosopher's meal count
 *
 * Increases the meals_eaten counter and checks if the philosopher has reached
 * their meal limit. If so, marks them as full using mutex protection.
 *
 * @param data Pointer to the philosopher's data structure
 * @return t_error SUCCESS on success, ERROR on mutex failure
 */
static t_error	increase_meals_eaten(t_philo *data)
{
	pthread_mutex_t	*mutex;

	if (!data->input->has_meal_limit)
		return (SUCCESS);
	data->meals_eaten++;
	if (data->meals_eaten < data->input->meal_limit)
		return (SUCCESS);
	mutex = data->mutexes.full;
	if (w_mutex(LOCK, mutex))
		return (ERROR);
	*data->full = true;
	if (w_mutex(UNLOCK, mutex))
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Handles the philosopher's eating action
 *
 * Coordinates the entire eating process including:
 * - Locking forks
 * - Printing eating state
 * - Updating last meal time
 * - Sleeping for time_to_eat duration
 * - Unlocking forks
 * - Updating meals eaten count
 *
 * @param data Pointer to the philosopher's data structure
 * @return t_error SUCCESS on success, ERROR on any failure
 */
t_error	philo_eat(t_philo *data)
{
	t_error	error;
	t_ms	timestamp;

	error = philo_forks(LOCK, data);
	if (error != SUCCESS)
		return (error);
	timestamp = 0;
	error = print_state(EATING, &timestamp, data);
	if (error != SUCCESS)
	{
		philo_forks(UNLOCK, data);
		return (error);
	}
	if (set_last_meal(timestamp, data) != SUCCESS)
	{
		philo_forks(UNLOCK, data);
		return (ERROR);
	}
	error = thread_sleep(data->input->time_to_eat, data);
	if (philo_forks(UNLOCK, data) != SUCCESS)
		return (ERROR);
	return (increase_meals_eaten(data));
}

/**
 * @brief Handles the philosopher's sleeping action
 *
 * Prints the sleeping state and sleeps for time_to_sleep duration.
 *
 * @param data Pointer to the philosopher's data structure
 * @return t_error SUCCESS on success, ERROR on print failure
 */
t_error	philo_sleep(t_philo *data)
{
	t_error	error;

	error = print_state(SLEEPING, NULL, data);
	if (error)
		return (error);
	error = thread_sleep(data->input->time_to_sleep, data);
	return (error);
}

/**
 * @brief Handles the philosopher's thinking action
 *
 * Prints the thinking state.
 *
 * @param data Pointer to the philosopher's data structure
 * @return t_error SUCCESS on success, ERROR on print failure
 */
t_error	philo_think(t_philo *data)
{
	t_error	error;

	error = print_state(THINKING, NULL, data);
	if (error)
		return (error);
	if (data->input->philo_count != 3)
		return (SUCCESS);
	return (thread_sleep(data->input->time_to_think, data));
}
