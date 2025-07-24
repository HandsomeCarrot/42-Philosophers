/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:23:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 17:46:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static t_error	mutex_fork(t_mutex_action action, pthread_mutex_t *fork,
		t_philo *data)
{
	t_error	error;

	if (!fork || !data)
		return (error_msg("missing parameters", "mutex_fork"));
	if (w_mutex(action, fork))
		return (ERROR);
	if (action == UNLOCK)
		return (SUCCESS);
	if (termination_requested(data->term_flag, data->mutexes.term_flag))
	{
		w_mutex(UNLOCK, fork);
		return (TERMINATE);
	}
	error = print_state(FORK, NULL, data);
	if (error != SUCCESS)
		w_mutex(UNLOCK, fork);
	return (error);
}

// docs
static t_error	philo_forks(t_mutex_action action, t_philo *data)
{
	t_error			error;

	error = mutex_fork(action, data->mutexes.first_fork, data);
	if (error != SUCCESS)
		return (error);
	error = mutex_fork(action, data->mutexes.second_fork, data);
	if (error != SUCCESS && action == LOCK)
		mutex_fork(UNLOCK, data->mutexes.first_fork, data);
	return (error);
}

// docs
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

// docs
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

// docs
static t_error	philo_eat(t_philo *data)
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

// docs
static t_error	philo_sleep(t_philo *data)
{
	t_error	error;

	error = print_state(SLEEPING, NULL, data);
	if (error)
		return (error);
	error = thread_sleep(data->input->time_to_sleep, data);
	return (error);
}

// docs
static t_error	philo_think(t_philo *data)
{
	t_error	error;

	error = print_state(THINKING, NULL, data);
	if (error)
		return (error);
	error = thread_sleep(data->input->time_to_think, data);
	return (error);
}

// docs
static t_error	solo_routine(t_philo *data)
{
	return (print_state(FORK, NULL, data));
}

// docs
static t_error	philo_routine(t_philo *data)
{
	t_error	error;

	if (data->input->philo_count == 1)
		return (solo_routine(data));
	error = SUCCESS;
	while (error == SUCCESS)
	{
		error = philo_eat(data);
		if (error == SUCCESS)
			error = philo_sleep(data);
		if (error == SUCCESS)
			error = philo_think(data);
	}
	return (error);
}

// docs 
void	*philo_start(void *ptr)
{
	t_philo	*data;
	t_error	error;

	if (!ptr)
		return ((void *)error_msg("missing parameters", "philo_start"));
	data = ptr;
	if (data->input->time_to_die == 0)
		return ((void*)TERMINATE);
	error = wait_for_start(data->mutexes.start);
	if (error != SUCCESS)
		return ((void *)error);
	if (termination_requested(data->term_flag, data->mutexes.term_flag))
		return ((void *)SUCCESS);
	if (data->input->philo_count > 1)
	{
		error = thread_sleep(data->initial_think_time, data);
		if (error != SUCCESS)
			return ((void *)error);
	}
	error = philo_routine(data);
	if (error == ERROR)
		set_termination_flag(data->term_flag, data->mutexes.term_flag);
	return ((void *)error);
}
