/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 14:24:41 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
int	initialize_structs(t_program **program_ptr)
{
	t_program	*program;
	
	if (!program_ptr)
		return (ERROR);
	*program_ptr = ft_calloc(1, sizeof(t_program));
	if (!*program_ptr)
	{
		error_msg("memory allocation failed", "initialization.c:35");
		return (ERROR);
	}
	program = *program_ptr;
	program->config = ft_calloc(1, sizeof(t_config));
	if (!program->config)
	{
		error_msg("memory allocation failed", "initialization.c:41");
		return (ERROR);
	}
	program->mutexes = ft_calloc(1, sizeof(t_mutex_data));
	if (!program->mutexes)
	{
		error_msg("memory allocation failed", "initialization.c:47");
		return (ERROR);
	}
	return (SUCCESS);
}

// docs
int	initialize_mutexes(t_program *program)
{
	unsigned int	pos;
	int				status;

	if (!program)
		return (ERROR);
	program->mutexes->forks = ft_calloc(program->config->number_of_philos + 1,
			sizeof(pthread_mutex_t *));
	if (!program->mutexes->forks)
		return (ERROR);
	pos = 0;
	while (pos < program->config->number_of_philos)
	{
		status = pthread_mutex_init(program->mutexes->forks[pos], NULL);
		if (status != 0)
			return (ERROR);
		pos++;
	}
	status = pthread_mutex_init(program->mutexes->stop, NULL);
	if (status != 0)
		return (ERROR);
	return (SUCCESS);
}

// docs
int	initialize_philos(t_program *program)
{
	unsigned int	pos;
	int				status;

	if (!program)
		return (1);
	program->philos = ft_calloc(program->config->number_of_philos + 1,
			sizeof(t_philo));
	if (!program->philos)
		return (1);
	pos = 0;
	while (pos < program->config->number_of_philos)
	{
		status = gettimeofday(program->philos[pos]->last_meal, NULL);
		if (status != 0)
			return (1);
		status = pthread_create(program->philos[pos]->thread, NULL, routine,
				program);
		if (status != 0)
			return (1);
		pos++;
	}
	return (0);
}
