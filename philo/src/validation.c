/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 17:03:17 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	handle_special_cases(t_config *config)
{
	if (config->number_of_philos < 1)
	{
		error_msg("There has to be at least 1 Philosopher");
		return (1);
	}
	if (config->time_to_die < 1
		|| config->time_to_eat < 1
		|| config->time_to_sleep < 1
		|| config->time_to_sleep < 1)
	{
		error_msg("Actions have to take at least 1ms (1)");
		return (1);
	}
	return (0);
}

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
	config->time_to_die = ft_atoui(argv[2], &error);
	config->time_to_eat = ft_atoui(argv[3], &error);
	config->time_to_sleep = ft_atoui(argv[4], &error);
	if (argc == 6)
	{
		config->number_of_meals = ft_atoui(argv[5], &error);
		if (!error && config->number_of_meals == 0)
			printf("Number of meals set to 0 (will be handled as unlimited)\n");
	}
	if (error)
		return (1);
	if (handle_special_cases(config))
		return (1);
	return (0);
}
