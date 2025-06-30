/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 15:09:46 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
void	process_input(int argc, char **argv, t_program *program)
{
	if (!argv || !program)
		exit_philo(ERROR, program);
	program->philo_count = ft_atoms((const char *)argv[1], program);
	program->input.time_to_die = ft_atoms((const char *)argv[2], program);
	program->input.time_to_eat = ft_atoms((const char *)argv[3], program);
	program->input.time_to_sleep = ft_atoms((const char *)argv[4], program);
	if (argc == 6)
	{
		program->input.meal_limit = ft_atoms((const char *)argv[5], program);
		program->input.has_meal_limit = true;
	}
	else
		program->input.has_meal_limit = false;
}

// docs
static pthread_mutex_t	*new_mutex(t_program *program)
{
	pthread_mutex_t	*new_mutex;

	if (!program)
		exit_philo(ERROR, program);
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
	t_ms	fork_index;
	t_ms	philo_count;

	if (!program)
		exit_philo(ERROR, program);
	program->mutexes.print = new_mutex(program);
	program->mutexes.stop = new_mutex(program);
	philo_count = program->philo_count;
	program->mutexes.forks = w_calloc(philo_count + 1,
			sizeof(pthread_mutex_t *), program);
	fork_index = 0;
	while (fork_index < philo_count)
	{
		program->mutexes.forks[fork_index] = new_mutex(program);
		fork_index++;
	}
}

// docs
void	initialize_data(int argc, char **argv, t_program **program_ptr)
{
	t_program	*program;
	t_ms	philo_count;

	if (!program_ptr)
	{
		error_msg("missing program struct pointer", NULL);
		exit_philo(ERROR, NULL);
	}
	*program_ptr = w_calloc(1, sizeof(t_program), NULL);
	program = *program_ptr;
	process_input(argc, argv, program);
	initialize_mutexes(program);
	philo_count = program->philo_count;
	program->philos = w_calloc(program->philo_count, sizeof(t_philo), program);
	program->error = SUCCESS;
}
