/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 15:06:39 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
void	set_error(t_error error, int *error_flag, t_mutexes *mutexes)
{
	if (!mutexes || !error_flag || !mutexes)
		return ;
	w_mutex(LOCK, mutexes->stop);
	*error_flag = error;
	w_mutex(UNLOCK, mutexes->stop);
}

// docs
void	get_error(int *error_flag, t_mutexes *mutexes)
{
	int	error;

	if (!error_flag || !mutexes)
		return ;
	w_mutex(LOCK, mutexes->stop);
	error = *error_flag;
	w_mutex(UNLOCK, mutexes->stop);
}

// docs
// TODO
void	*routine_start(void *data)
{
	t_philo	*philo;

	philo = data;
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %lu\n", philo->id);
	w_mutex(UNLOCK, philo->mutexes->print);
	return (NULL);
}
