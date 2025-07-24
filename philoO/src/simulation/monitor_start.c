/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:25:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 11:33:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static t_error	check_philos(void)
{
	
}

// docs
static t_error	monitor_routine(t_monitor *data)
{
	while (!termination_requested(data->term_flag, data->term_mutex))
	{
		// check death
		// check full
	}
}

// docs
void	*monitor_start(void *ptr)
{
	t_monitor	*data;
	t_error		error;

	if (!ptr)
		return ((void *)error_msg("missing parameters", "philo_start"));
	data = ptr;
	error = wait_for_start(data->input, data->start_mutex);
	if (error)
		return ((void *)error);
	error = monitor_routine(data);
	return ((void *)error);
}