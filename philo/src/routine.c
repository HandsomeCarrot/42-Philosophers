/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 11:57:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
void	set_stop_flag(t_program *program)
{
	pthread_mutex_lock(program->mutexes->stop);
	if (!program->stop_flag)
		program->stop_flag = 1;
	pthread_mutex_unlock(program->mutexes->stop);
}

// docs
static int	get_stop_flag(t_program *program)
{
	int	current_stop_flag;

	pthread_mutex_lock(program->mutexes->stop);
	current_stop_flag = program->stop_flag;
	pthread_mutex_unlock(program->mutexes->stop);
	return (current_stop_flag);
}

// docs
void	*routine(t_program *program)
{
	while (!get_stop_flag(program))
	{
		//routine
	}
}
