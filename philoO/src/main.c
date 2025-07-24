/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 17:01:41 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_error	error;

	if (argc < 5 || argc > 6)
		return (error_msg("Incorrect input", "wrong amount of arguments"));
	data = NULL;
	error = initialize_data(argc, argv, &data);
	if (!error && start_simulation(data) != SUCCESS)
	{
		error = ERROR;
		set_termination_flag(&data->term_flag, &data->mutexes.term_mutex);
	}
	if (erase_data(data) != SUCCESS)
		error = ERROR;
	return (error);
}
