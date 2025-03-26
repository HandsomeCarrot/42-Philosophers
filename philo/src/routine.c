/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/26 13:19:25 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_stop_flag(t_program *program)
{
	pthread_mutex_lock(program->mutexes->stop);
	if (!program->stop_flag)
		program->stop_flag = 1;
	pthread_mutex_unlock(program->mutexes->stop);
}

static int	get_stop_flag(t_program *program)
{
	int	current_stop_flag;

	pthread_mutex_lock(program->mutexes->stop);
	current_stop_flag = program->stop_flag;
	pthread_mutex_unlock(program->mutexes->stop);
	return (current_stop_flag);
}

void	*routine(t_program *program)
{
	while (!get_stop_flag(program))
	{
		//routine
	}
}
