/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 20:30:04 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
// TODO
void	*philo_start(void *data)
{
	t_philo	*philo;
	t_ms	start;

	philo = data;
	if (wait_for_start(philo->mutexes->forks[philo->id]))
		return (thread_error(philo->term_flag_ptr, philo->mutexes));
	if (is_termination_requested(philo->term_flag_ptr, philo->mutexes))
		return ((void *)SUCCESS);
	// temp code
	get_time_in_ms(&start, philo->mutexes);
	start -= philo->input->sim_start_time;
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %llu after: %llu ms\n", philo->id, start);
	w_mutex(UNLOCK, philo->mutexes->print);
	// end of temp code
	return ((void *)SUCCESS);
}
