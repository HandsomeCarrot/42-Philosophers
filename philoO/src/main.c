/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/17 12:37:17 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		error_msg("Incorrect amount of Arguments", get_exec_spattern());
		return (ERROR);
	}
	data = initialize_data(argc, argv);
	if (!data)
	{
		cleanup_program(false, data);
		return (ERROR);
	}
	if (start_simulation(data) != SUCCESS)
	{
		cleanup_program(true, data);
		return (ERROR);
	}
	return (cleanup_program(false, data));
}
