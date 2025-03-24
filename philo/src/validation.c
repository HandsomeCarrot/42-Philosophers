/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 16:31:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static unsigned int	ft_atoui(const char *nptr, int *error)
{
	long long	res;
	char		*str;

	res = 0;
	str = (char *)nptr;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			error_msg("Non-numeric character found: ");
			error_msg(str);
			*error = 1;
			return (0);
		}
		res = res * 10 + (*nptr - '0');
		if (res > UINT_MAX)
		{
			error_msg("(Overflow) argument is too large: ");
			error_msg(str);
			*error = 1;
			return (0);
		}
		nptr++;
	}
	return ((unsigned int)res);
}

int	validate_input(int argc, char **argv, t_config *config)
{
	int	error;
	
	error = 0;
	config->number_of_philos = ft_atoui(argv[1], &error);
	if (error)
		return (1);
	config->time_to_die = ft_atoui(argv[2], &error);
	if (error)
		return (1);
	config->time_to_eat = ft_atoui(argv[3], &error);
	if (error)
		return (1);
	config->time_to_sleep = ft_atoui(argv[4], &error);
	if (error)
		return (1);
	if (argc == 6)
	{
		config->number_of_meals = ft_atoui(argv[5], &error);
		if (error)
			return (1);
	}
	return (0);
}
