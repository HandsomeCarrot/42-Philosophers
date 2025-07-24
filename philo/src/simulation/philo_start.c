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

/**
 * @brief Handle mutex operations on individual forks with termination checking
 * @param action LOCK to acquire fork, UNLOCK to release fork
 * @param fork Pointer to the fork mutex
 * @param data Philosopher data for termination checking and state printing
 * @return SUCCESS on success, TERMINATE if termination requested, ERROR on failure
 */
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

/**
 * @brief Acquire or release both forks for a philosopher
 * @param action LOCK to acquire both forks, UNLOCK to release both forks
 * @param data Philosopher data containing fork mutex pointers
 * @return SUCCESS on success, TERMINATE if termination requested, ERROR on failure
 */
t_error	philo_forks(t_mutex_action action, t_philo *data)
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

/**
 * @brief Special routine for single philosopher scenario
 * @param data Philosopher data
 * @return Result of fork state printing
 */
static t_error	solo_routine(t_philo *data)
{
	return (print_state(FORK, NULL, data));
}

/**
 * @brief Main philosopher routine loop: eat, sleep, think
 * @param data Philosopher data
 * @return SUCCESS if completed normally, TERMINATE if termination requested, ERROR on failure
 */
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

/**
 * @brief Main philosopher thread entry point
 * @param ptr Philosopher data cast to void pointer
 * @return Thread return value cast to void pointer
 */
void	*philo_start(void *ptr)
{
	t_philo	*data;
	t_error	error;

	if (!ptr)
		return ((void *)error_msg("missing parameters", "philo_start"));
	data = ptr;
	if (data->input->time_to_die == 0)
		return ((void *)TERMINATE);
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
