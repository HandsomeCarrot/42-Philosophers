/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:18:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:21:44 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Initializes a philosopher's data structure with given parameters.
 *
 * Sets up a philosopher's ID, mutexes, input parameters, termination flag,
 * meal tracking variables, and initial think time.
 *
 * @param id The philosopher's unique identifier (0-based index).
 * @param philo Pointer to the philosopher's data structure to initialize.
 * @param data Pointer to the shared simulation data structure.
 * @return SUCCESS on successful initialization, ERROR on failure.
 */
static t_error	init_philo(t_count id, t_philo *philo, t_data *data)
{
	philo->id = id;
	assign_mutexes(philo, data);
	philo->input = &data->input;
	philo->term_flag = &data->term_flag;
	philo->last_meal = &data->philos.last_meals[philo->id];
	philo->full = &data->philos.philo_full[philo->id];
	philo->initial_think_time = calculate_initial_think_time(id);
	return (SUCCESS);
}

/**
 * @brief Initializes all philosopher data structures in the simulation.
 *
 * Iterates through all philosophers and initializes each one's data structure
 * using init_philo(). Handles error cases during initialization.
 *
 * @param data Pointer to the shared simulation data structure.
 * @return SUCCESS if all philosophers initialized successfully, ERROR otherwise.
 */
static t_error	init_all_philos(t_data *data)
{
	t_count	index;

	index = 0;
	while (index < data->input.philo_count)
	{
		if (init_philo(index, &data->philos.philo_data[index], data))
			return (ERROR);
		index++;
	}
	return (SUCCESS);
}

/**
 * @brief Creates and initializes all philosopher-related data structures.
 *
 * Allocates memory for meal tracking, fullness flags, and philosopher data.
 * Initializes each philosopher's data structure via init_all_philos().
 *
 * @param data Pointer to the shared simulation data structure.
 * @return SUCCESS if all allocations and initializations succeed, ERROR if any
 *         memory allocation fails or initialization encounters an error.
 * @note Uses w_calloc() for memory allocation which handles error cases.
 */
t_error	create_philo_data(t_data *data)
{
	t_count	philos;

	philos = data->input.philo_count;
	data->philos.last_meals = w_calloc(philos, sizeof(t_ms));
	if (!data->philos.last_meals)
		return (ERROR);
	data->philos.philo_full = w_calloc(philos, sizeof(bool));
	if (!data->philos.philo_full)
		return (ERROR);
	data->philos.philo_data = w_calloc(philos, sizeof(t_philo));
	if (!data->philos.philo_data)
		return (ERROR);
	if (init_all_philos(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
