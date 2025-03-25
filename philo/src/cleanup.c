/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:06:51 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/25 16:14:56 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	clean_philos(t_philo **philos)
{
	unsigned int	i;

	i = 0;
	while (philos[i])
	{
		pthread_join(philos[i]->thread, NULL);
		free(philos[i]->last_meal);
	}
}

static void	clean_mutexes(t_mutex_data *mutexes)
{
	unsigned int	i;
	int				status;

	i = 0;
	while (mutexes->forks[i])
	{
		status = pthread_mutex_destroy(mutexes->forks[i]);
		if (status == EBUSY)
		{
			pthread_mutex_unlock(mutexes->forks[i]);
			pthread_mutex_destroy(mutexes->forks[i]);
		}
		i++;
	}
	status = pthread_mutex_destroy(mutexes->death);
	if (status == EBUSY)
	{
		pthread_mutex_unlock(mutexes->death);
		pthread_mutex_destroy(mutexes->death);
	}
}

void	cleanup(t_program *program)
{
	if (program->config)
		free(program->config);
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
	free(program);
}
