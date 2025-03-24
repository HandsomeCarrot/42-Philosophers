/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 17:18:31 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strlen(char *str)
{
	int	counter;

	counter = 0;
	while (str && *str)
	{
		counter++;
		str++;
	}
	return (counter);
}

void	error_msg(char *msg)
{
	static int	first_error;

	if (!first_error)
	{
		write(STDERR_FILENO, "Error!\n", sizeof(char) * 7);
		first_error = 1;
	}
	if (msg)
	{
		write(STDERR_FILENO, msg, sizeof(char) * ft_strlen(msg));
		write(STDERR_FILENO, "\n", sizeof(char) * 1);
	}
}

void	exit_philo(char *msg, t_params *config, int exit_code)
{
	if (msg)
		error_msg(msg);
	if (config)
		cleanup(config);
	error_msg("Aborting program");
	exit(exit_code);
}
