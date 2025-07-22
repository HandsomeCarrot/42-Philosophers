/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 00:12:12 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_error	error;

	if (argc < 5 || argc > 6)
		return (error_msg("Incorrect amount of Arguments", get_exec_pattern()));
	data = NULL;
	error = initialize_data(argc, argv, &data);
	if (!error)
	{
		error = start_simulation(data);
		if (error)
			set_termination_flag(&data->term_flag, &data->mutexes.term_mutex);
	}
	erase_data(data);
	return (error);
}
