/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/09 13:53:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
	// temp code
	get_elapsed_time_ms(&start, philo->input);
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %llu after: %llu ms\n", philo->id, start);
	w_mutex(UNLOCK, philo->mutexes->print);
	// end of temp code
	return ((void *)SUCCESS);
}
