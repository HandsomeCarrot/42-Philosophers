/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/10 15:28:52 by vpoka            ###   ########.fr       */
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
	interval = 5;
	while (time > 0)
	{
		if (time < interval)
			sleep_time = time;
		else
			sleep_time = interval;
		if (usleep(sleep_time * 1000) != 0)
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
	t_ms	right_fork;
	t_ms	left_fork;
	t_ms	id;

	if (!first || !second || !philo)
	{
		error_msg("missing parameters", "get_philo_forks");
		return (ERROR);
	}
	id = philo->id;
	right_fork = id;
	left_fork = id + 1;
	if (id == philo->input->philo_count)
		left_fork = 0;
	if (id % 2 == 0)
	{
		*first = philo->mutexes->forks[right_fork];
		*second = philo->mutexes->forks[left_fork];
	}
	*first = philo->mutexes->forks[left_fork];
	*second = philo->mutexes->forks[right_fork];
	return (SUCCESS);
}

// docs
static t_error	mutex_fork(t_mutex_action action, pthread_mutex_t *fork,
		t_philo *philo)
{
	if (!fork || !philo)
	{
		error_msg("missing parameters", "mutex_fork");
		return (ERROR);
	}
	if (w_mutex(action, fork))
		return (ERROR);
	if (action == LOCK)
	{
		if (print_philo_state(FORK, philo))
		{
			w_mutex(UNLOCK, fork);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

// docs
static t_error	philo_forks(t_mutex_action action, t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!philo)
	{
		error_msg("missing parameters", "philo_forks");
		return (ERROR);
	}
	if (get_philo_forks(&first_fork, &second_fork, philo))
		return (ERROR);
	if (mutex_fork(action, first_fork, philo))
		return (ERROR);
	if (mutex_fork(action, second_fork, philo))
	{
		if (action == LOCK)
			mutex_fork(UNLOCK, first_fork, philo);
		return (ERROR);
	}
	return (SUCCESS);
}

// docs
static t_error	eat(t_philo *philo)
{
	t_error	error;

	if (!philo)
	{
		error_msg("missing parameters", "eat");
		return (ERROR);
	}
	if (termination_requested(philo->term_flag_ptr, philo->mutexes))
			return (TERMINATE);
	if (philo_forks(LOCK, philo))
		return (ERROR);
	if (print_philo_state(EATING, philo))
		return (ERROR);
	error = thread_sleep(philo->input->time_to_eat, philo);
	if (philo_forks(UNLOCK, philo))
		return (ERROR);
	return (error);
}

// docs
static t_error	sleep(t_philo *philo)
{
	(void)philo;
	// TODO
	return (SUCCESS);
}

// docs
static t_error	think(t_philo *philo)
{
	(void)philo;
	// TODO
	return (SUCCESS);
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
		error = eat(philo);
		if (error == SUCCESS)
			error = sleep(philo);
		if (error == SUCCESS)
			error = think(philo);
		if (error == SUCCESS)
		{
			if (termination_requested(philo->term_flag_ptr, philo->mutexes))
				error = TERMINATE;
		}
	}
	return (error);
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
	t_ms	start;
	t_error	error;

	if (!data)
	{
		error_msg("missing parameters", "philo_start");
		return ((void *)ERROR);
	}
	philo = data;
	if (wait_for_start(philo->mutexes->forks[philo->id]))
		return (handle_thread_error(philo->term_flag_ptr, philo->mutexes));
	if (termination_requested(philo->term_flag_ptr, philo->mutexes))
		return ((void *)SUCCESS);
	error = start_routine(philo);
	if (error == ERROR)
		set_termination_flag(philo->term_flag_ptr, philo->mutexes);
	return ((void *)error);
}
