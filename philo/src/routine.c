/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 02:04:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
void	set_error(t_error error, t_program *program)
{
	if (!program || !program->mutexes)
		return ;
	if (pthread_mutex_lock(program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, 0, program->mutexes->print);
		safe_putstr_fd("failed to lock stop mutex\n", 2, STDERR_FILENO, program->mutexes->print);
		return ;
	}
	program->error = error;
	if (pthread_mutex_unlock(program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, 0, program->mutexes->print);
		safe_putstr_fd("failed to unlock stop mutex\n", STDERR_FILENO, 2, program->mutexes->print);
	}
}

// docs
t_error	get_error(t_program *program)
{
	int	error;

	if (!program || !program->mutexes)
		return (ERROR);
	if (pthread_mutex_lock(program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, 0, program->mutexes->print);
		safe_putstr_fd("failed to lock stop mutex\n", STDERR_FILENO, 2, program->mutexes->print);
		return (ERROR);
	}
	error = program->error;
	if (pthread_mutex_unlock(program->mutexes->stop))
	{
		safe_putstr_fd("-philo: ", STDERR_FILENO, 0, program->mutexes->print);
		safe_putstr_fd("failed to unlock stop mutex\n", STDERR_FILENO, 2, program->mutexes->print);
		return (ERROR);
	}
	return (error);
}

// docs
// TODO
void	*routine_start(void *data)
{
	t_philo	*philo;
	char	*current_time;

	philo = data;
	safe_putstr_fd("started philo number: ", STDOUT_FILENO, 0, philo->mutexes->print);
	current_time = mstoa(philo->id);
	safe_putstr_fd(current_time, STDOUT_FILENO, 1, philo->mutexes->print);
	safe_putstr_fd("\n", STDOUT_FILENO, 2, philo->mutexes->print);
	free(current_time);
	free(data);
	return (NULL);
}
