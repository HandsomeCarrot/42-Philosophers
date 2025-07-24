/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:00:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:24:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Assigns monitor-related data structures to the monitor object.
 *
 * This function initializes the monitor structure by assigning pointers to
 * various shared data structures and mutexes that the monitor thread will
 * need to access during simulation. It sets up references to input data,
 * philosopher status information, and synchronization primitives.
 *
 * @param data Pointer to the main program data structure containing all
 *             simulation data and synchronization primitives.
 *             Must not be NULL.
 *
 * @note This function does not allocate any memory but simply assigns
 *       existing pointers to the monitor structure.
 * @warning The data parameter must point to a fully initialized t_data
 *          structure before calling this function.
 */
void	assign_monitor_data(t_data *data)
{
	t_monitor		*monitor;
	t_all_mutexes	*mutexes;

	monitor = &data->monitor;
	mutexes = &data->mutexes;
	monitor->input = &data->input;
	monitor->philos.meal_mutexes = mutexes->meal_mutexes;
	monitor->philos.last_meals = data->philos.last_meals;
	monitor->philos.full_mutexes = mutexes->full_mutexes;
	monitor->philos.philo_full = data->philos.philo_full;
	monitor->philos.philo_data = data->philos.philo_data;
	monitor->term_mutex = &mutexes->term_mutex;
	monitor->term_flag = &data->term_flag;
	monitor->print_mutex = &mutexes->print_mutex;
	monitor->start_mutex = &mutexes->start_mutexes[data->input.philo_count];
}
