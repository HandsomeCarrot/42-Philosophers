/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 19:04:04 by vpoka            ###   ########.fr       */
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
	return (SUCCESS);
}

// docs
// TODO
void	*routine_start(void *data)
{
	t_philo	*philo;
	t_ms	start;

	philo = data;
	if (wait_for_start(philo) != SUCCESS)
		return ((void *)ERROR);
	if (get_time_in_ms(&start, philo->mutexes))
		return ((void *)ERROR);
	start -= philo->input->sim_start_time;
	if (w_mutex(LOCK, philo->mutexes->print))
		return ((void *)ERROR);
	printf("started philo number: %llu after: %llu ms\n", philo->id, start);
	if (w_mutex(UNLOCK, philo->mutexes->print))
		return ((void *)ERROR);
	return ((void *)SUCCESS);
}
