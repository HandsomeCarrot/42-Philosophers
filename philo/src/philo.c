/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 17:18:31 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_params	*config;

	if (argc < 5 || argc > 6)
		exit_philo("Incorrect amount of Arguments", NULL, 1);
	config = NULL;
	if (initialize_structs(&config))
		exit_philo("Initialization failed", config, 1);
	if (validate_input(argc, argv, config))
		exit_philo("Input is faulty", config, 1);
	cleanup(config);
	exit(0);
}
