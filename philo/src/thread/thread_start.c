/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/05 18:12:03 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
static t_error	wait_for_start(t_philo *philo)
{
	if (w_mutex(LOCK, philo->mutexes->forks[philo->id]) != SUCCESS)
		return (ERROR);
	if (w_mutex(UNLOCK, philo->mutexes->forks[philo->id]) != SUCCESS)
		return (ERROR);
	if (is_termination_requested(philo->term_flag_ptr, philo->mutexes))
		return (TERM_REQ);
	return (SUCCESS);
}

// docs
// TODO
void	*philo_start(void *data)
{
	t_philo	*philo;
	t_ms	start;
	t_error	error;

	philo = data;
	error = wait_for_start(philo);
	if (error != SUCCESS)
		return (return_thread_error(error, philo->term_flag_ptr,
				philo->mutexes));
	// temp code
	get_time_in_ms(&start, philo->mutexes);
	start -= philo->input->sim_start_time;
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %llu after: %llu ms\n", philo->id, start);
	w_mutex(UNLOCK, philo->mutexes->print);
	// end of temp code
	return ((void *)SUCCESS);
}

void	*monitor_start(void *data)
{
	t_program	*program;

	program = (t_program *)data;
	return (return_thread_error(SUCCESS, &program->terminate_threads,
			&program->mutexes));
}
