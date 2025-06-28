/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/28 21:24:10 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static pthread_mutex_t	*new_mutex(t_program *program)
{
	pthread_mutex_t	*new_mutex;

	new_mutex = w_calloc(1, sizeof(pthread_mutex_t), program);
	if (pthread_mutex_init(new_mutex, NULL))
	{
		error_msg("failed to create mutex", NULL);
		free(new_mutex);
		exit_philo(ERROR, program);
	}
	return (new_mutex);
}

// docs
static void	initialize_mutexes(t_program *program)
{
	t_mutexes	*mutexes;
	t_ms		fork_index;
	t_ms		nbr_of_philos;

	if (!program)
		return (ERROR);
	program->mutexes = w_calloc(1, sizeof(t_mutexes), program);
	mutexes = program->mutexes;
	mutexes->print = new_mutex(program);
	mutexes->stop = new_mutex(program);
	mutexes->forks = w_calloc(get(NBR_OF_PHILOS) + 1, sizeof(pthread_mutex_t *),
			program);
	fork_index = 0;
	nbr_of_philos = get(NBR_OF_PHILOS);
	while (fork_index < nbr_of_philos)
	{
		mutexes->forks[fork_index] = new_mutex(program);
		fork_index++;
	}
}

// docs
static void	initialize_philos(t_program *program)
{
	pthread_t	*philos;
	t_ms		nbr_of_philos;

	nbr_of_philos = get(NBR_OF_PHILOS);
	philos = w_calloc(nbr_of_philos, sizeof(t_philo *), program);
}

// docs
void	initialize_data(int argc, char **argv, t_program **program_ptr)
{
	t_program	*program;

	if (!program_ptr)
	{
		error_msg("missing program struct pointer", NULL);
		exit_philo(ERROR, NULL);
	}
	*program_ptr = w_calloc(1, sizeof(t_program), NULL);
	program = *program_ptr;
	if (initialize_config(argc, argv))
		exit_philo(ERROR, program);
	initialize_mutexes(program);
	initialize_philos(program);
	program->error = SUCCESS;
}
