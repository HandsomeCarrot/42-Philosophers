/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 19:07:33 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static int	initialize_structs(t_program **program_ptr)
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
static int	initialize_universal_mutexes(t_mutexes *mutexes)
{
	t_ms	fork_index;

	if (!mutexes)
		return (ERROR);
	if (pthread_mutex_init(mutexes->stop, NULL) != SUCCESS)
		return (ERROR);
	if (pthread_mutex_init(mutexes->print, NULL) != SUCCESS)
		return (ERROR);
	mutexes->forks = ft_calloc(get(NBR_OF_PHILOS), sizeof(pthread_mutex_t *));
	if (!mutexes->forks)
		return (ERROR);
	fork_index = 0;
	while (fork_index < get(NBR_OF_PHILOS))
	{
		if (pthread_mutex_init(mutexes->forks, NULL) != SUCCESS)
			return (ERROR);
		fork_index++;
	}
	return (SUCCESS);
}

int	initialize_data(int argc, char **argv, t_program **program_ptr)
{
	t_program	*program;

	if (initialize_structs(program_ptr) != SUCCESS)
		return (ERROR);
	program = *program_ptr;
	if (initialize_config(argc, argv) != SUCCESS)
		return (ERROR);
	if (initialize_universal_mutexes(program->mutexes) != SUCCESS)
	{
		error_msg("Initialization of mutexes failed", NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

// docs
t_philo	*create_philo(t_ms id, t_program *program)
{
	t_philo	*new_philo;

	new_philo = ft_calloc(1, sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->meals_eaten = 0;
	new_philo->id = id;
	if (get_time_in_ms(&(new_philo->last_meal)))
	{
		free(new_philo);
		return (NULL);
	}
	if (pthread_create(&(new_philo->thread), NULL, &routine, program))
	{
		// safe_putstr() "failed to create philo x"
		free(new_philo);
		return (NULL);
	}
	return (new_philo);
}

// docs
int	initialize_philos(t_program *program)
{
	t_ms	philo_index;

	if (!program)
		return (1);
	program->philos = ft_calloc(get(NBR_OF_PHILOS), sizeof(t_philo *));
	if (!program->philos)
		return (ERROR);
	philo_index = 0;
	while (philo_index < get(NBR_OF_PHILOS))
	{
		program->philos[philo_index] = create_philo(philo_index, program);
		if (!program->philos[philo_index])
			return (ERROR);
		philo_index++;
	}
	return (SUCCESS);
}
