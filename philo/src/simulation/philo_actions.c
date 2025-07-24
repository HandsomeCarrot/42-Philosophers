/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:32:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/01/04 16:32:00 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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

t_error	philo_sleep(t_philo *data)
{
	t_error	error;

	error = print_state(SLEEPING, NULL, data);
	if (error)
		return (error);
	error = thread_sleep(data->input->time_to_sleep, data);
	return (error);
}

t_error	philo_think(t_philo *data)
{
	t_error	error;

	error = print_state(THINKING, NULL, data);
	if (error)
		return (error);
	error = thread_sleep(data->input->time_to_think, data);
	return (error);
}
