/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 18:37:04 by vpoka            ###   ########.fr       */
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
	if (initialize_data(argc, argv, &program) != SUCCESS)
		exit_philo(program, ERROR);
	if (initialize_philos(program) != SUCCESS)
		exit_philo("Initialization of philosophers failed", program, ERROR);
	exit_philo(NULL, program, SUCCESS);
}
