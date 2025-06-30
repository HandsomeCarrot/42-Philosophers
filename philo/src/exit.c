/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 01:24:21 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static void	join_philos(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;

	if (!program || !program->philos)
		return ;
	philo_index = 0;
	philo_count = program->philo_count;
	while (philo_index < philo_count)
	{
		if (pthread_join(program->philos[philo_index].thread, NULL))
		{
			set_error(ERROR, program);
			print_error("failed to join thread: ", mstoa(philo_index));
		}
		philo_index++;
	}
}

// docs
void	free_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		error_msg("failed to destroy mutex", NULL);
	free(mutex);
}

// docs
static void	clean_mutexes(t_program *program)
{
	t_ms	fork_index;
	t_ms	fork_count;

	if (!program || !program->mutexes)
		return ;
	if (program->mutexes.stop)
		free_mutex(program->mutexes->stop);
	if (program->mutexes.print)
		free_mutex(program->mutexes->print);
	if (!program->mutexes.forks)
		return ;
	fork_index = 0;
	fork_count = program->philo_count;
	while (fork_index < fork_count || !program->mutexes.forks[fork_index])
	{
		free_mutex(program->mutexes.forks[fork_index]);
		fork_index++;
	}
	free(program->mutexes.forks);
}

// docs
// is it all I need to free?
static void	cleanup(t_program *program)
{
	if (program->philos)
	{
		join_philos(program);
		free(program->philos);
	}
	if (program->mutexes)
	{
		clean_mutexes(program);
		free(program->mutexes);
	}
	free(program);
}

// docs
void	exit_philo(t_error error, t_program *program)
{
	if (program)
		cleanup(program);
	exit(error);
}
