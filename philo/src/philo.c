/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/25 16:52:21 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
		exit_philo("Incorrect amount of Arguments", NULL, 1);
	program = NULL;
	if (initialize_structs(&program))
		exit_philo("Initialization of structs failed", program, 1);
	if (validate_input(argc, argv, program))
		exit_philo("Input is faulty", program, 1);
	if (initialize_mutexes(program))
		exit_philo("Initialization of mutexes failed", program, 1);
	cleanup(program);
	exit(0);
}
