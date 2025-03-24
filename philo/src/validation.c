/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 18:44:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	handle_special_cases(t_program *program)
{
	if (program->config->number_of_philos < 1)
	{
		error_msg("There has to be at least 1 Philosopher");
		return (1);
	}
	if (program->config->time_to_die < 1
		|| program->config->time_to_eat < 1
		|| program->config->time_to_sleep < 1
		|| program->config->time_to_sleep < 1)
	{
		error_msg("Actions have to take at least 1 micro-second (1)");
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
			error_msg("Non-numeric character found in string:");
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

int	validate_input(int argc, char **argv, t_program *program)
{
	int	error;

	error = 0;
	program->config->number_of_philos = ft_atoui(argv[1], &error);
	program->config->time_to_die = ft_atoui(argv[2], &error);
	program->config->time_to_eat = ft_atoui(argv[3], &error);
	program->config->time_to_sleep = ft_atoui(argv[4], &error);
	if (argc == 6)
	{
		program->config->number_of_meals = ft_atoui(argv[5], &error);
		if (!error && program->config->number_of_meals == 0)
			printf("Number of meals set to 0 (will be handled as no input)\n");
	}
	else
		program->config->number_of_meals = 0;
	if (error)
		return (1);
	if (handle_special_cases(program))
		return (1);
	return (0);
}
