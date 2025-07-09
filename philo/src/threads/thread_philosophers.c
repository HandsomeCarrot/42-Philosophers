/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/09 19:33:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
static t_error	thread_sleep(t_ms time, t_philo *philo)
{
	(void)time;
	(void)philo;
	// TODO
	return (SUCCESS);
}

// docs
static t_error	get_philo_forks(pthread_mutex_t **left, pthread_mutex_t **right,
		t_philo *philo)
{
	(void)left;
	(void)right;
	(void)philo;
	// TODO
	return (SUCCESS);
}

// docs
static t_error	philo_forks(t_mutex_action action, t_philo *philo)
{
	(void)action;
	(void)philo;
	// TODO
	return (SUCCESS);
}

// docs
static t_error	eat(t_philo *philo)
{
	(void)philo;
	// TODO
	return (SUCCESS);
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

	philo = data;
	if (wait_for_start(philo->mutexes->forks[philo->id]))
		return (handle_thread_error(philo->term_flag_ptr, philo->mutexes));
	if (termination_requested(philo->term_flag_ptr, philo->mutexes))
		return ((void *)SUCCESS);
	while (!termination_requested(philo->term_flag_ptr, philo->mutexes))
	{
		if (eat(philo))
			return ((void *)ERROR);
		if (sleep(philo))
			return ((void *)ERROR);
		if (think(philo))
			return ((void *)ERROR);
	}
	return ((void *)SUCCESS);
}
