/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:23:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 15:23:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs 
void	*philo_start(void *data)
{
	t_philo	*philo;
	t_error	error;

	if (!data)
		return ((void *)error_msg("missing parameters", "philo_start"));
	error = wait_for_start(*philo->input, philo->mutexes.start);
	if (error != SUCCESS)
		return ((void *)error);
	if (termination_requested(philo->term_flag, philo->mutexes.term_flag))
		return ((void *)SUCCESS);
	philo = data;
	
	return ((void *)SUCCESS);
}