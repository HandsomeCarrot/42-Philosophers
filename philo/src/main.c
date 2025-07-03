/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/03 21:49:05 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
int	main(int argc, char **argv)
{
	t_program	*program;
	t_error		err;

	if (argc < 5 || argc > 6)
	{
		error_msg("Incorrect amount of Arguments", get_exec_pattern());
		return (ERR_ARG);
	}
	program = NULL;
	err = initialize_data(argc, argv, &program);
	if (err != SUCCESS)
	{
		cleanup_program(program);
		return (err);
	}
	err = start_simulation(program);
	if (err != SUCCESS)
	{
		cleanup_program(program);
		return (err);
	}
	cleanup_program(program);
	return (SUCCESS);
}
