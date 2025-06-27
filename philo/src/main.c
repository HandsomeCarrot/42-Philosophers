/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 16:24:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
	{
		error_msg("Incorrect amount of Arguments", get_exec_pattern());
		exit_philo(NULL, ERROR);
	}
	program = NULL;
	if (initialize_structs(&program) != SUCCESS)
		exit_philo(program, ERROR);
	if (initialize_config(argc, argv) != SUCCESS)
		exit_philo(program, ERROR);
	if (initialize_universal_mutexes(program) != SUCCESS)
	{
		error_msg("Initialization of mutexes failed", NULL);
		exit_philo(program, ERROR);
	}
	if (initialize_philos(program) != SUCCESS)
		exit_philo("Initialization of philosophers failed", program, ERROR);
	exit_philo(NULL, program, SUCCESS);
}
