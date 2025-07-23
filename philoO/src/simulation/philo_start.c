/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:23:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 15:47:50 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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
		error = philo_eat(philo);
		if (error == SUCCESS)
			error = philo_sleep(philo);
		if (error == SUCCESS)
			error = philo_think(philo);
	}
	return (error);
}

// docs 
void	*philo_start(void *data)
{
	t_philo	*philo;
	t_error	error;

	if (!data)
		return ((void *)error_msg("missing parameters", "philo_start"));
	philo = data;
	error = wait_for_start(philo->input, philo->mutexes.start);
	if (error != SUCCESS)
		return ((void *)error);
	if (termination_requested(philo->term_flag, philo->mutexes.term_flag))
		return ((void *)SUCCESS);
	error = start_routine(philo);
	if (error == ERROR)
		set_termination_flag(philo->term_flag, philo->mutexes.term_flag);
	return ((void *)error);
}