/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/11 20:21:37 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Processes and validates command-line arguments.
 *
 * Parses input arguments and stores them in the program's configuration
 * structure. Handles both mandatory and optional meal limit arguments.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param program Pointer to the main program structure to populate.
 *
 * @return SUCCESS on valid input, ERROR otherwise.
 *
 * @note Exits with error if arguments are invalid or pointers are NULL.
 */
static t_error	process_input(int argc, char **argv, t_program *program)
{
	if (!argv || !program)
	{
		error_msg("missing parameters", "process_input");
		return (ERROR);
	}
	if (atoms((const char *)argv[1], &program->input.philo_count) != SUCCESS)
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
	program->input.time_to_think = 0;
	if (program->input.philo_count % 2 == 1)
		program->input.time_to_think = 1;
	return (SUCCESS);
}

/**
 * @brief Allocates and initializes a new mutex.
 *
 * Allocates memory for a pthread_mutex_t and initializes it. Handles
 * allocation and initialization errors by logging and returning NULL.
 *
 * @param program Pointer to the main program structure for error handling.
 *
 * @return Pointer to the initialized mutex, or NULL on failure.
 *
 * @note Exits with error on allocation or initialization failure.
 */
static pthread_mutex_t	*new_mutex(t_program *program)
{
	pthread_mutex_t	*new_mutex;

	if (!program)
	{
		error_msg("missing parameters", "new_mutex");
		return (NULL);
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

/**
 * @brief Initializes a mutex array for the simulation.
 *
 * Allocates and initializes an array of mutexes with the specified count.
 *
 * @param program Pointer to the main program structure.
 * @param mutex_array_ptr Pointer to the mutex array to initialize.
 * @param count Number of mutexes to create.
 *
 * @return SUCCESS if all mutexes are initialized, ERROR otherwise.
 */
static t_error	initialize_mutex_array(t_program *program,
		pthread_mutex_t ***mutex_array_ptr, t_ms count)
{
	t_ms			index;
	pthread_mutex_t	**mutexes;

	if (!program || !mutex_array_ptr)
	{
		error_msg("missing parameters", "initialize_mutex_array");
		return (ERROR);
	}
	mutexes = w_calloc(count, sizeof(pthread_mutex_t *));
	if (!mutexes)
		return (ERROR);
	*mutex_array_ptr = mutexes;
	index = 0;
	while (index < count)
	{
		mutexes[index] = new_mutex(program);
		if (!mutexes[index])
			return (ERROR);
		index++;
	}
	return (SUCCESS);
}

/**
 * @brief Initializes all mutexes required for the simulation.
 *
 * Creates print, term_flag, fork, last_meal and meals_eaten mutexes.
 *
 * @param program Pointer to the main program structure.
 *
 * @return SUCCESS if all mutexes are initialized, ERROR otherwise.
 *
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
	program->mutexes.term_flag = new_mutex(program);
	if (!program->mutexes.term_flag)
		return (ERROR);
	if (initialize_mutex_array(program, &program->mutexes.forks,
			program->input.philo_count) != SUCCESS)
		return (ERROR);
	if (initialize_mutex_array(program, &program->mutexes.last_meal,
			program->input.philo_count) != SUCCESS)
		return (ERROR);
	if (initialize_mutex_array(program, &program->mutexes.meals_eaten,
			program->input.philo_count) != SUCCESS)
		return (ERROR);
	if (initialize_mutex_array(program, &program->mutexes.start_mutexes,
			program->input.philo_count) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Initializes the main program data structure.
 *
 * Allocates memory for the program structure, processes input arguments,
 * initializes mutexes, and allocates memory for philosophers.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param program_ptr Double pointer to the program structure to initialize.
 *
 * @return SUCCESS if initialization was successful, ERROR otherwise.
 *
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
	program->philos = w_calloc(program->input.philo_count, sizeof(t_philo));
	if (!program->philos)
		return (ERROR);
	program->term_flag = false;
	return (SUCCESS);
}
