/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 16:13:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static t_config	*get_config(void)
{
	static t_config	config;

	return (&config);
}

// docs
static int	convert_input(int argc, char **argv, t_config *config)
{
	bool	error;

	error = false;
	config->number_of_philos = ft_atoui(argv[1], &error);
	if (error)
		return (ERROR);
	config->time_to_die = ft_atoui(argv[2], &error);
	if (error)
		return (ERROR);
	config->time_to_eat = ft_atoui(argv[3], &error);
	if (error)
		return (ERROR);
	config->time_to_sleep = ft_atoui(argv[4], &error);
	if (error)
		return (ERROR);
	if (argc == 6)
	{
		config->number_of_meals = ft_atoui(argv[5], &error);
		if (error)
			return (ERROR);
	}
	return (SUCCESS);
}

// docs
int	initialize_config(int argc, char **argv)
{
	if (convert_input(argc, argv, get_config()) != SUCCESS)
		return (ERROR);
	if (get_config()->number_of_philos < 1)
	{
		error_msg("There has to be at least 1 Philosopher", NULL);
		return (ERROR);
	}
	if (argc == 6)
		get_config()->simulate_until_death = false;
	else
		get_config()->simulate_until_death = true;
	return (SUCCESS);
}

// docs
unsigned int	get(int data_to_get)
{
	if (data_to_get == NBR_OF_PHILOS)
		return (get_config()->number_of_philos);
	if (data_to_get == TIME_TO_DIE)
		return (get_config()->time_to_die);
	if (data_to_get == TIME_TO_EAT)
		return (get_config()->time_to_eat);
	if (data_to_get == TIME_TO_SLEEP)
		return (get_config()->time_to_sleep);
	if (data_to_get == NBR_OF_MEALS)
		return (get_config()->number_of_meals);
	return (0);
}

// docs
bool	simulate_until_deat(void)
{
	return (get_config()->simulate_until_death);
}
