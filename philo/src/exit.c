/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/28 21:45:53 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static void	clean_philos(t_program *program)
{
	t_ms	nbr_of_philos;
	t_ms	philo_index;

	if (!program || !program->philos)
		return ;
	philo_index = 0;
	nbr_of_philos = get(NBR_OF_PHILOS);
	while (philo_index < nbr_of_philos)
	{
		if (pthread_join(program->philos[philo_index], NULL))
		{
			set_error(ERROR, program);
			safe_putstr_fd("failed to join thread: ", STDERR_FILENO, program);
			safe_putstr_fd(mstoa(philo_index), STDERR_FILENO, program);
			safe_putstr_fd("\n", STDERR_FILENO, program);
		}
		philo_index++;
	}
}

void	free_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
}

// TODO
static void	clean_mutexes(t_program *program)
{
	t_ms	fork_index;
	int		status;

	if (!program || !program->mutexes)
		return ;
	if (program->mutexes->forks)
	{
		fork_index = 0;
		while (fork_index < get(NBR_OF_PHILOS))
		{
			free_mutex(program->mutexes->forks[fork_index]);
			fork_index++;
		}
		free(program->mutexes->forks);
	}
	if (program->mutexes->stop)
		free_mutex(program->mutexes->stop);
	if (program->mutexes->print)
		free_mutex(program->mutexes->print);
}

// TODO
static void	cleanup(t_program *program)
{
	if (program->philos)
	{
		clean_philos(program);
		free(program->philos);
	}
	if (program->mutexes)
	{
		clean_mutexes(program);
		free(program->mutexes);
	}
	free(program);
}

// TODO
void	exit_philo(t_error error, t_program *program)
{
	if (program)
		cleanup(program);
	exit(error);
}
