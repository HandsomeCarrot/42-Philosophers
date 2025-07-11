/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/11 18:35:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
static t_error	thread_sleep(t_ms time, t_philo *philo)
{
	t_ms	interval;
	t_ms	sleep_time;

	if (!philo)
	{
		error_msg("missing parameters", "thread_sleep");
		return (ERROR);
	}
	interval = 10000;
	while (time > 0)
	{
		if (time < interval)
			sleep_time = time;
		else
			sleep_time = interval;
		if (usleep(sleep_time * MS_TO_USEC) != 0)
			return (ERROR);
		if (termination_requested(philo->term_flag_ptr, philo->mutexes))
			return (TERMINATE);
		time -= sleep_time;
	}
	return (SUCCESS);
}

// docs
static t_error	get_philo_forks(pthread_mutex_t **first,
		pthread_mutex_t **second, t_philo *philo)
{
	t_ms	own_fork;
	t_ms	neighbors_fork;
	t_ms	id;

	if (!first || !second || !philo)
	{
		error_msg("missing parameters", "get_philo_forks");
		return (ERROR);
	}
	id = philo->id;
	own_fork = id;
	neighbors_fork = (id + 1) % philo->input->philo_count;
	if (id % 2 == 0)
	{
		*first = philo->mutexes->forks[own_fork];
		*second = philo->mutexes->forks[neighbors_fork];
		return (SUCCESS);
	}
	*first = philo->mutexes->forks[neighbors_fork];
	*second = philo->mutexes->forks[own_fork];
	return (SUCCESS);
}

// docs
static t_error	mutex_fork(t_mutex_action action, pthread_mutex_t *fork,
		t_philo *philo)
{
	t_error	error;

	if (!fork || !philo)
	{
		error_msg("missing parameters", "mutex_fork");
		return (ERROR);
	}
	if (w_mutex(action, fork))
		return (ERROR);
	if (action == UNLOCK)
		return (SUCCESS);
	error = print_philo_state(FORK, philo);
	if (error != SUCCESS)
		w_mutex(UNLOCK, fork);
	return (error);
}

// docs
static t_error	philo_forks(t_mutex_action action, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_error			error;

	if (!philo)
	{
		error_msg("missing parameters", "philo_forks");
		return (ERROR);
	}
	if (get_philo_forks(&first_fork, &second_fork, philo))
		return (ERROR);
	error = mutex_fork(action, first_fork, philo);
	if (error != SUCCESS)
		return (error);
	error = mutex_fork(action, second_fork, philo);
	if (error != SUCCESS)
	{
		if (action == LOCK)
			mutex_fork(UNLOCK, first_fork, philo);
		return (error);
	}
	return (SUCCESS);
}

// docs
static t_error	set_last_meal(t_philo *philo)
{
	t_ms	current_time;
	pthread_mutex_t	*mutex;

	if (!philo)
	{
		error_msg("missing parameters", "set_last_meal");
		return (ERROR);
	}
	if (get_current_time_ms(&current_time))
		return (ERROR);
	mutex = philo->mutexes->last_meal[philo->id];
	if (w_mutex(LOCK, mutex))
		return (ERROR);
	philo->last_meal = current_time;
	if (w_mutex(UNLOCK, mutex))
		return (ERROR);
	return (SUCCESS);
}

// docs
static t_error	increase_meals_eaten(t_philo *philo)
{
	pthread_mutex_t	*mutex;

	if (!philo)
	{
		error_msg("missing parameters", "increase_meals_eaten");
		return (ERROR);
	}
	mutex = philo->mutexes->meals_eaten[philo->id];
	if (w_mutex(LOCK, mutex))
		return (ERROR);
	philo->meals_eaten++;
	if (w_mutex(UNLOCK, mutex))
		return (ERROR);
	return (SUCCESS);
}

// docs
static t_error	philo_eat(t_philo *philo)
{
	t_error	error;

	if (!philo)
	{
		error_msg("missing parameters", "philo_eat");
		return (ERROR);
	}
	error = philo_forks(LOCK, philo);
	if (error != SUCCESS)
		return (error);
	if (set_last_meal(philo))
		return (ERROR);
	error = print_philo_state(EATING, philo);
	if (error != SUCCESS)
		return (error);
	error = thread_sleep(philo->input->time_to_eat, philo);
	if (philo_forks(UNLOCK, philo))
		return (ERROR);
	if (increase_meals_eaten(philo))
		return (ERROR);
	return (error);
}

// docs
static t_error	philo_sleep(t_philo *philo)
{
	t_error	error;

	if (!philo)
	{
		error_msg("missing parameters", "philo_sleep");
		return (ERROR);
	}
	error = print_philo_state(SLEEPING, philo);
	if (error != SUCCESS)
		return (error);
	error = thread_sleep(philo->input->time_to_sleep, philo);
	return (error);
}

// docs
static t_error	philo_think(t_philo *philo)
{
	t_error	error;

	if (!philo)
	{
		error_msg("missing parameters", "philo_think");
		return (ERROR);
	}
	error = print_philo_state(THINKING, philo);
	if (error != SUCCESS)
		return (error);
	//error = thread_sleep(1, philo);
	return (error);
}

// docs
static t_error	start_routine(t_philo *philo)
{
	t_error	error;

	if (!philo)
	{
		error_msg("missing parameters", "routine");
		return (ERROR);
	}
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
static t_error	handle_single_philo(t_philo *philo)
{
	t_error	error;

	if (!philo)
	{
		error_msg("missing parameters", "handle_single_philo");
		return (ERROR);
	}
	error = mutex_fork(LOCK, philo->mutexes->forks[0], philo);
	if (error != SUCCESS)
		return (error);
	return (mutex_fork(UNLOCK, philo->mutexes->forks[0], philo));
}

/**
 * @brief Entry point for a philosopher thread.
 *
 * Waits for the simulation to start, then enters the philosopher's main
 * routine. Handles thread termination and outputs start timing.
 *
 * @param data Pointer to the philosopher's data structure.
 *
 * @return Pointer to SUCCESS on normal completion, or ERROR on failure.
 *
 * @note Returns immediately if the termination flag is set.
 */
void	*philo_start(void *data)
{
	t_philo	*philo;
	t_error	error;

	if (!data)
	{
		error_msg("missing parameters", "philo_start");
		return ((void *)ERROR);
	}
	philo = data;
	if (philo->input->time_to_die == 0)
		return ((void *)SUCCESS);
	if (wait_for_start(philo->mutexes->start_mutexes[philo->id]))
		return (handle_thread_error(philo->term_flag_ptr, philo->mutexes));
	if (termination_requested(philo->term_flag_ptr, philo->mutexes))
		return ((void *)SUCCESS);
	if (philo->input->philo_count == 1)
		error = handle_single_philo(philo);
	else
		error = start_routine(philo);
	if (error == ERROR)
		set_termination_flag(philo->term_flag_ptr, philo->mutexes);
	return ((void *)error);
}
