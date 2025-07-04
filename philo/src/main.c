/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 18:08:50 by vpoka            ###   ########.fr       */
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
