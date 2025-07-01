/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 17:29:37 by vpoka            ###   ########.fr       */
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
void	process_input(int argc, char **argv, t_program *program)
{
	if (!argv || !program)
		exit_philo(ERROR, program);
	program->philo_count = atoms((const char *)argv[1], program);
	program->input.time_to_die = atoms((const char *)argv[2], program);
	program->input.time_to_eat = atoms((const char *)argv[3], program);
	program->input.time_to_sleep = atoms((const char *)argv[4], program);
	if (argc == 6)
	{
		program->input.meal_limit = atoms((const char *)argv[5], program);
		program->input.has_meal_limit = true;
	}
	else
		program->input.has_meal_limit = false;
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

/**
 * @brief Initializes all mutexes required for the simulation.
 *
 * Creates print, stop, and fork mutexes. Allocates and initializes an array
 * of fork mutexes based on philosopher count.
 *
 * @param program Pointer to the main program structure.
 * @note Exits with error if program pointer is NULL.
 */
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
void	initialize_data(int argc, char **argv, t_program **program_ptr)
{
	t_program	*program;
	t_ms		philo_count;

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
