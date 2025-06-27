/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 22:17:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
// look over
static void	clean_philos(t_philo **philos)
{
	unsigned int	i;

	i = 0;
	while (philos && philos[i])
	{
		pthread_join(philos[i]->thread, NULL);
		free(philos[i]->last_meal);
	}
}

// docs
// look over
static void	clean_mutexes(t_mutexes *mutexes)
{
	unsigned int	i;
	int				status;

	i = 0;
	while (mutexes->forks && mutexes->forks[i])
	{
		status = pthread_mutex_destroy(mutexes->forks[i]);
		if (status == EBUSY)
		{
			pthread_mutex_unlock(mutexes->forks[i]);
			pthread_mutex_destroy(mutexes->forks[i]);
		}
		i++;
	}
	if (mutexes->stop)
	{
		status = pthread_mutex_destroy(mutexes->stop);
		if (status == EBUSY)
		{
			pthread_mutex_unlock(mutexes->stop);
			pthread_mutex_destroy(mutexes->stop);
		}
	}
}

// docs
// look over
static void	cleanup(t_program *program)
{
	if (program->philos)
	{
		clean_philos(program->philos);
		free(program->philos);
	}
	if (program->mutexes)
	{
		clean_mutexes(program);
		free(program->mutexes);
	}
	if (program->config)
		free(program->config);
	free(program);
}

// docs
// look over
void	exit_philo(t_program *program, int exit_code)
{
	if (program)
		cleanup(program);
	exit(exit_code);
}
