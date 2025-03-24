/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 17:19:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;

	if (argc < 5 || argc > 6)
		exit_philo("Incorrect amount of Arguments", NULL, 1);
	params = NULL;
	if (initialize_structs(&params))
		exit_philo("Initialization failed", params, 1);
	if (validate_input(argc, argv, params))
		exit_philo("Input is faulty", params, 1);
	cleanup(params);
	exit(0);
}
