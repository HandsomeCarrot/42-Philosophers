/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 11:31:50 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Processes and validates command-line arguments for the simulation.
 *
 * Parses input arguments into the program's configuration structure. Handles
 * both mandatory and optional arguments (meal limit).
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param program Pointer to the main program structure.
 * @note Exits with error if arguments are invalid or pointers are NULL.
 */
static t_error	process_input(int argc, char **argv, t_program *program)
{
	if (!argv || !program)
	{
		error_msg("missing parameters", "process_input");
		return (ERROR);
	}
	if (atoms((const char *)argv[1], &program->philo_count) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[2], &program->input.time_to_die) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[3], &program->input.time_to_eat) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[4], &program->input.time_to_sleep) != SUCCESS)
		return (ERROR);
	if (argc == 6)
	{
		if (atoms((const char *)argv[5], &program->input.meal_limit) != SUCCESS)
			return (ERROR);
		program->input.has_meal_limit = true;
	}
	else
		program->input.has_meal_limit = false;
	return (SUCCESS);
}

/**
 * @brief Creates and initializes a new mutex.
 *
 * Allocates memory for a mutex and initializes it. Handles allocation failures
 * and initialization errors by exiting the program.
 *
 * @param program Pointer to the main program structure for error handling.
 * @return Pointer to the initialized mutex on success.
 * @note Exits with error on allocation or initialization failure.
 */
static pthread_mutex_t	*new_mutex(t_program *program)
{
	pthread_mutex_t	*new_mutex;

	if (!program)
	{
		error_msg("missing parameters", "new_mutex");
		return (ERROR);
	}
	new_mutex = w_calloc(1, sizeof(pthread_mutex_t));
	if (!new_mutex)
		return (NULL);
	if (pthread_mutex_init(new_mutex, NULL))
	{
		error_msg("failed to create mutex", NULL);
		free(new_mutex);
		return (NULL);
	}
	return (new_mutex);
}

// docs
static t_error	initialize_forks(t_program *program)
{
	t_ms			fork_index;
	t_ms			fork_count;
	pthread_mutex_t	**forks;

	fork_index = 0;
	fork_count = program->philo_count;
	forks = w_calloc(fork_count, sizeof(pthread_mutex_t *));
	if (!forks)
		return (ERROR);
	program->mutexes.forks = forks;
	while (fork_index < fork_count)
	{
		forks[fork_index] = new_mutex(program);
		if (!forks[fork_index])
			return (ERROR);
		fork_index++;
	}
	return (SUCCESS);
}

/**
 * @brief Initializes all mutexes required for the simulation.
 *
 * Creates print, stop, and fork mutexes. Allocates and initializes an array
 * of fork mutexes based on philosopher count.
 *
 * @param program Pointer to the main program structure.
 * @note Exits with error if program pointer is NULL.
 */
static t_error	initialize_mutexes(t_program *program)
{
	if (!program)
	{
		error_msg("missing parameters", "initialize_mutexes");
		return (ERROR);
	}
	program->mutexes.print = new_mutex(program);
	if (!program->mutexes.print)
		return (ERROR);
	program->mutexes.stop = new_mutex(program);
	if (!program->mutexes.stop)
		return (ERROR);
	if (initialize_forks(program) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Initializes the main program data structure.
 *
 * Allocates memory for program structure, processes input arguments,
 * initializes mutexes, and allocates memory for philosophers.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param program_ptr Double pointer to the program structure to initialize.
 * @note Exits with error if program_ptr is NULL or allocation fails.
 */
t_error	initialize_data(int argc, char **argv, t_program **program_ptr)
{
	t_program	*program;

	if (!program_ptr)
	{
		error_msg("missing parameters", "initialize_data");
		return (ERROR);
	}
	*program_ptr = w_calloc(1, sizeof(t_program));
	program = *program_ptr;
	if (!program)
		return (ERROR);
	if (process_input(argc, argv, program) != SUCCESS)
		return (ERROR);
	if (initialize_mutexes(program) != SUCCESS)
		return (ERROR);
	program->philos = w_calloc(program->philo_count, sizeof(t_philo));
	if (!program->philos)
		return (ERROR);
	program->terminate_threads = false;
	return (SUCCESS);
}
