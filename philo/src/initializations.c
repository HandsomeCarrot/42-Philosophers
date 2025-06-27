/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 16:12:55 by vpoka            ###   ########.fr       */
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
		error_msg("memory allocation failed", NULL);
		return (ERROR);
	}
	program = *program_ptr;
	program->mutexes = ft_calloc(1, sizeof(t_mutexes));
	if (!program->mutexes)
	{
		error_msg("memory allocation failed", NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

// docs
int	initialize_universal_mutexes(t_mutexes *mutexes)
{
	int	pos;

	if (!mutexes)
		return (ERROR);
	if (pthread_mutex_init(mutexes->stop, NULL) != SUCCESS)
		return (ERROR);
	if (pthread_mutex_init(mutexes->print, NULL) != SUCCESS)
		return (ERROR);
	pos = 0;
	mutexes->forks = ft_calloc(get(NBR_OF_PHILOS), sizeof(pthread_mutex_t *));
	while (pos < get(NBR_OF_PHILOS))
	{
		if (pthread_mutex_init(mutexes->forks, NULL) != SUCCESS)
			return (ERROR);
		pos++;
	}
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
