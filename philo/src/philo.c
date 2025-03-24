/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:21:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 13:57:41 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_config	*config;

	if (argc < 5 || argc > 6)
		exit_philo("Incorrect amount of Arguments", 1);
	config = NULL;
	if (initialize_structs(config))
		exit_philo("Initialization failed", 1);
	printf("%s", *argv);
	exit(0);
}
