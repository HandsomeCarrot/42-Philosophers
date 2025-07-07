/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:46:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 20:37:09 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// docs
void	*monitor_start(void *data)
{
	t_program	*program;

	program = (t_program *)data;
	if (wait_for_start(program->mutexes.forks[0]))
		return (thread_error(&program->terminate_threads, &program->mutexes));
	// check each thread if
	// 	dead?
	// all threads full?
	// set? thread termination flag
	// wait a bit after all checks
	// loop until term flag is set
	return ((void *)SUCCESS);
}
