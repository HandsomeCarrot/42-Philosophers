/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 23:18:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Initializes the main program and mutexes structures.
 *
 * This function allocates memory for the main `t_program` structure and
 * the nested `t_mutexes` structure. It handles null pointer checks and
 * potential memory allocation failures.
 *
 * @param program_ptr A pointer to a `t_program` pointer. This will be
 *                    modified to point to the newly allocated program
 *                    structure.
 * @return Returns `SUCCESS` (0) on successful allocation and
 *         initialization, or `ERROR` (1) if memory allocation fails or
 *         the input pointer is null.
 */
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

/**
 * @brief Initializes all mutexes required for the simulation.
 *
 * This function initializes the `stop` and `print` mutexes, and then
 * allocates and initializes a mutex for each fork based on the number of
 * philosophers.
 *
 * @param mutexes A pointer to the `t_mutexes` struct that holds all the
 *                mutex variables to be initialized.
 * @return Returns `SUCCESS` (0) if all mutexes are initialized
 *         correctly, or `ERROR` (1) if any `pthread_mutex_init` call
 *         fails or if memory allocation for the fork mutexes fails.
 */
static int	initialize_mutexes(t_mutexes *mutexes)
{
	t_ms	fork_index;

	if (!mutexes)
		return (ERROR);
	if (pthread_mutex_init(&mutexes->stop, NULL) != SUCCESS)
		return (ERROR);
	if (pthread_mutex_init(&mutexes->print, NULL) != SUCCESS)
		return (ERROR);
	mutexes->forks = ft_calloc(get(NBR_OF_PHILOS), sizeof(pthread_mutex_t *));
	if (!mutexes->forks)
		return (ERROR);
	fork_index = 0;
	while (fork_index < get(NBR_OF_PHILOS))
	{
		if (pthread_mutex_init(&mutexes->forks[fork_index], NULL) != SUCCESS)
			return (ERROR);
		fork_index++;
	}
	return (SUCCESS);
}

/**
 * @brief Orchestrates the complete initialization of the simulation data.
 *
 * This function serves as the main entry point for initialization. It
 * calls helper functions to initialize the core data structures, parse
 * the command-line arguments into the program's configuration, and
 * initialize all necessary mutexes.
 *
 * @param argc The argument count from the program's entry point.
 * @param argv The argument vector from the program's entry point,
 *             containing the simulation parameters.
 * @param program_ptr A pointer to a `t_program` pointer that will be
 *                    allocated and fully initialized by this function.
 * @return Returns `SUCCESS` (0) if all initialization steps are
 *         completed without errors, otherwise returns `ERROR` (1).
 */
int	initialize_data(int argc, char **argv, t_program **program_ptr)
{
	t_program	*program;

	if (initialize_structs(program_ptr))
		return (ERROR);
	program = *program_ptr;
	if (initialize_config(argc, argv))
		return (ERROR);
	if (initialize_mutexes(program->mutexes))
	{
		error_msg("Initialization of mutexes failed", NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Creates and initializes a single philosopher instance.
 *
 * This function allocates memory for a new `t_philo` struct, sets its
 * initial state (ID, meals eaten, last meal time), and creates the
 * philosopher's execution thread, which starts running the `routine`.
 *
 * @param id The unique identifier for the new philosopher.
 * @param program A pointer to the main `t_program` structure, providing
 *                access to shared data and mutexes.
 * @return Returns a pointer to the newly created `t_philo` on success.
 *         Returns `NULL` if memory allocation fails, if the current time
 *         cannot be retrieved, or if the thread creation fails.
 * @note This function has a significant side effect: it spawns a new
 *       thread using `pthread_create`.
 */
t_philo	*create_philo(t_ms id, t_program *program)
{
	t_philo	*new_philo;

	new_philo = ft_calloc(1, sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->meals_eaten = 0;
	new_philo->id = id;
	if (get_time_in_ms(&new_philo->last_meal, program))
	{
		free(new_philo);
		return (NULL);
	}
	if (pthread_create(&new_philo->thread, NULL, &routine, program))
	{
		safe_putstr_fd("failed to create philo ", STDERR_FILENO, program);
		safe_putstr_fd(mstoa(id), STDERR_FILENO, program);
		free(new_philo);
		return (NULL);
	}
	return (new_philo);
}

/**
 * @brief Initializes and launches all philosopher threads.
 *
 * This function allocates an array to hold pointers to all `t_philo`
 * structs. It then iterates, calling `create_philo` for each
 * philosopher to create and launch their respective threads.
 *
 * @param program A pointer to the main `t_program` structure, which will
 *                contain the array of philosophers.
 * @return Returns `SUCCESS` (0) if all philosophers are created and
 *         launched successfully. Returns `ERROR` (1) if the initial
 *         array allocation fails or if any philosopher creation fails.
 */
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
