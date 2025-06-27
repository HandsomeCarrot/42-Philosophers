/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/28 01:28:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
void	set_error(t_error error, t_program *program)
{
	if (!program || !program->mutexes)
		return ;
	if (pthread_mutex_lock(&program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, program);
		safe_putstr_fd("failed to lock stop mutex\n", STDERR_FILENO, program);
		return ;
	}
	program->error = error;
	if (pthread_mutex_unlock(&program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, program);
		safe_putstr_fd("failed to unlock stop mutex\n", STDERR_FILENO, program);
	}
}

// docs
t_error	get_error(t_program *program)
{
	int	error;

	if (!program || !program->mutexes)
		return (ERROR);
	if (pthread_mutex_lock(&program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, program);
		safe_putstr_fd("failed to lock stop mutex\n", STDERR_FILENO, program);
		return (ERROR);
	}
	error = program->error;
	if (pthread_mutex_unlock(&program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, program);
		safe_putstr_fd("failed to unlock stop mutex\n", STDERR_FILENO, program);
		return (ERROR);
	}
	return (error);
}

// docs
// TODO
void	*routine(t_program *program)
{
	//routine
}
