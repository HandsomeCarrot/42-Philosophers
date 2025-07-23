/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:23:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 01:13:00 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static t_error	mutex_fork(t_mutex_action action, pthread_mutex_t *fork,
		t_philo *philo)
{
	t_error	error;

	if (!fork || !philo)
		return (error_msg("missing parameters", "mutex_fork"));
	if (w_mutex(action, fork))
		return (ERROR);
	if (action == UNLOCK)
		return (SUCCESS);
	if (termination_requested(philo->term_flag, philo->mutexes.term_flag))
	{
		w_mutex(UNLOCK, fork);
		return (TERMINATE);
	}
	error = print_state(FORK, NULL, philo);
	if (error != SUCCESS)
		w_mutex(UNLOCK, fork);
	return (error);
}

// docs
static t_error	philo_forks(t_mutex_action action, t_philo *philo)
{
	t_error			error;

	error = mutex_fork(action, philo->mutexes.first_fork, philo);
	if (error != SUCCESS)
		return (error);
	error = mutex_fork(action, philo->mutexes.second_fork, philo);
	if (error != SUCCESS && action == LOCK)
		mutex_fork(UNLOCK, philo->mutexes.first_fork, philo);
	return (error);
}

// docs
static t_error	set_last_meal(t_ms timestamp, t_philo *philo)
{
	pthread_mutex_t	*mutex;

	mutex = philo->mutexes.meal;
	if (w_mutex(LOCK, mutex))
		return (ERROR);
	*philo->last_meal = timestamp;
	if (w_mutex(UNLOCK, mutex))
		return (ERROR);
	return (SUCCESS);
}

// docs
static t_error	increase_meals_eaten(t_philo *philo)
{
	pthread_mutex_t	*mutex;

	if (!philo->input->has_meal_limit)
		return (SUCCESS);
	philo->meals_eaten++;
	if (philo->meals_eaten < philo->input->meal_limit)
		return (SUCCESS);
	mutex = philo->mutexes.full;
	if (w_mutex(LOCK, mutex))
		return (ERROR);
	*philo->full = true;
	if (w_mutex(UNLOCK, mutex))
		return (ERROR);
	return (SUCCESS);
}

// docs
static t_error	philo_eat(t_philo *philo)
{
	t_error	error;
	t_ms	timestamp;

	error = philo_forks(LOCK, philo);
	if (error != SUCCESS)
		return (error);
	timestamp = 0;
	error = print_state(EATING, &timestamp, philo);
	if (error != SUCCESS)
	{
		philo_forks(UNLOCK, philo);
		return (error);
	}
	if (set_last_meal(timestamp, philo) != SUCCESS)
	{
		philo_forks(UNLOCK, philo);
		return (ERROR);
	}
	error = thread_sleep(philo->input->time_to_eat, philo);
	if (philo_forks(UNLOCK, philo) != SUCCESS)
		return (ERROR);
	return (increase_meals_eaten(philo));
}

// docs
static t_error	start_routine(t_philo *philo)
{
	t_error	error;

	error = SUCCESS;
	while (error == SUCCESS)
	{
		error = philo_eat(philo);
		if (error == SUCCESS)
			error = philo_sleep(philo);
		if (error == SUCCESS)
			error = philo_think(philo);
	}
	return (error);
}

// docs 
void	*philo_start(void *data)
{
	t_philo	*philo;
	t_error	error;

	if (!data)
		return ((void *)error_msg("missing parameters", "philo_start"));
	philo = data;
	error = wait_for_start(philo->input, philo->mutexes.start);
	if (error != SUCCESS)
		return ((void *)error);
	if (termination_requested(philo->term_flag, philo->mutexes.term_flag))
		return ((void *)SUCCESS);
	error = start_routine(philo);
	if (error == ERROR)
		set_termination_flag(philo->term_flag, philo->mutexes.term_flag);
	return ((void *)error);
}
