/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 20:56:03 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Entry point for the philosophers program.
 *
 * Parses arguments, initializes resources, starts the simulation, and handles
 * cleanup on exit.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 *
 * @return EXIT_SUCCESS on success, ERROR otherwise.
 *
 * @note Handles error messages and resource cleanup for all failure cases.
 */
int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
	{
		error_msg("Incorrect amount of Arguments", get_exec_pattern());
		return (ERROR);
	}
	program = NULL;
	if (initialize_data(argc, argv, &program) != SUCCESS)
	{
		cleanup_program(false, program);
		return (ERROR);
	}
	if (start_simulation(program) != SUCCESS)
	{
		cleanup_program(true, program);
		return (ERROR);
	}
	return (cleanup_program(false, program));
}
