/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:08:16 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 14:23:47 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	convert_input(int argc, char **argv, t_program *program)
{
	bool	error;

	error = false;
	program->config->number_of_philos = ft_atoui(argv[1], &error);
	if (error)
	return (ERROR);
	program->config->time_to_die = ft_atoui(argv[2], &error);
	if (error)
	return (ERROR);
	program->config->time_to_eat = ft_atoui(argv[3], &error);
	if (error)
	return (ERROR);
	program->config->time_to_sleep = ft_atoui(argv[4], &error);
	if (error)
	return (ERROR);
	if (argc == 6)
	{
		program->config->number_of_meals = ft_atoui(argv[5], &error);
		if (error)
			return (ERROR);
	}
	return (SUCCESS);
}

// docs
static int	check_input(int argc, t_program *program)
{
	if (program->config->number_of_philos < 1)
	{
		error_msg("There has to be at least 1 Philosopher", NULL);
		return (ERROR);
	}
	if (argc == 6)
		program->config->eat_to_death = false;
	else
		program->config->eat_to_death = true;
	return (SUCCESS);
}

// docs
int	validate_input(int argc, char **argv, t_program *program)
{
	if (convert_input(argc, argv, program) != SUCCESS)
		return (ERROR);
	if (check_input(argc, program) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
