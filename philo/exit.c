/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:19:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/23 17:59:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	counter;

	counter = 0;
	while(str && *str)
	{
		counter++;
		str++;
	}
	return(counter);
}

void	exit_philo(char *msg, int exit_code)
{
	if (msg)
	{
		write(STDERR_FILENO, msg, sizeof(char) * ft_strlen(msg));
		free(msg);
	}
	exit(exit_code);
}