/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/02 16:24:21 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
// TODO
void	*routine_start(void *data)
{
	t_philo	*philo;
	t_ms	start;

	philo = data;
	get_time_in_ms(&start, philo->mutexes);
	start -= philo->input->sim_start_time;
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %llu after: %llu ms\n", philo->id, start);
	w_mutex(UNLOCK, philo->mutexes->print);
	return (NULL);
}
