/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 18:33:12 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Gets the singleton configuration instance.
 *
 * This function provides access to the single, static configuration instance
 * used throughout the program. The configuration is initialized once and
 * shared across all components.
 *
 * @return Pointer to the static t_config instance.
 */
static t_config	*get_config(void)
{
	static t_config	config;

	return (&config);
}

/**
 * @brief Converts and validates command line arguments into configuration.
 *
 * Parses the command line arguments, converts them to appropriate types,
 * and stores them in the configuration structure. Validates that
 * all numeric inputs are valid unsigned integers.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return SUCCESS (0) if all inputs were valid, ERROR (1) otherwise.
 */
static int	convert_input(int argc, char **argv)
{
	bool	error;

	error = false;
	get_config()->number_of_philos = ft_atoms(argv[1], &error);
	if (error)
		return (ERROR);
	get_config()->time_to_die = ft_atoms(argv[2], &error);
	if (error)
		return (ERROR);
	get_config()->time_to_eat = ft_atoms(argv[3], &error);
	if (error)
		return (ERROR);
	get_config()->time_to_sleep = ft_atoms(argv[4], &error);
	if (error)
		return (ERROR);
	if (argc == 6)
	{
		get_config()->number_of_meals = ft_atoms(argv[5], &error);
		if (error)
			return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Initializes the global configuration from command line arguments.
 *
 * Validates and sets up the program configuration based on the provided
 * command line arguments. Ensures there is at least 1 philosopher and
 * handles optional meal limit parameter.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return SUCCESS (0) if initialization succeeded, ERROR (1) otherwise.
 */
int	initialize_config(int argc, char **argv)
{
	if (convert_input(argc, argv) != SUCCESS)
		return (ERROR);
	if (get(NBR_OF_PHILOS) < 1)
	{
		error_msg("There has to be at least 1 Philosopher", NULL);
		return (ERROR);
	}
	if (argc == 6)
		get_config()->has_meal_limit = false;
	else
		get_config()->has_meal_limit = true;
	return (SUCCESS);
}

/**
 * @brief Retrieves a specific configuration value.
 *
 * Provides access to individual configuration parameters based on the
 * requested data type. Acts as a type-safe interface to the configuration.
 *
 * @param data_to_get Enum value specifying which configuration parameter
 *                    to retrieve (NBR_OF_PHILOS, TIME_TO_DIE, etc.).
 * @return The requested configuration value, or 0 if invalid request.
 */
t_ms	get(int data_to_get)
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
	if (data_to_get == HAS_MEAL_LIMIT)
		return ((t_ms)get_config()->has_meal_limit);
	return (0);
}
