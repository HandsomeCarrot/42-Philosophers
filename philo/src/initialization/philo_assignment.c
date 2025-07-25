/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_assignment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:45:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 04:16:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Assigns fork mutexes to a philosopher based on their ID.
 *
 * This function assigns the first and second forks to a philosopher in a way
 * that helps prevent deadlocks. Even-numbered philosophers get their own fork
 * first, while odd-numbered philosophers get their neighbor's fork first.
 *
 * @param philo Pointer to the philosopher structure to configure.
 * @param data Pointer to the shared program data containing all mutexes.
 */
static void	assign_forks(t_philo *philo, t_data *data)
{
	t_count	own_fork;
	t_count	next_fork;

	own_fork = philo->id;
	next_fork = (own_fork + 1) % data->input.philo_count;
	if (philo->id % 2 == 0)
	{
		philo->mutexes.first_fork = &data->mutexes.fork_mutexes[own_fork];
		philo->mutexes.second_fork = &data->mutexes.fork_mutexes[next_fork];
	}
	else
	{
		philo->mutexes.first_fork = &data->mutexes.fork_mutexes[next_fork];
		philo->mutexes.second_fork = &data->mutexes.fork_mutexes[own_fork];
	}
}

/**
 * @brief Assigns all necessary mutexes to a philosopher.
 *
 * Configures all mutex pointers in the philosopher structure including:
 * - Print mutex for synchronized output
 * - Termination flag mutex
 * - Meal mutex for tracking last meal time
 * - Full status mutex
 * - Start mutex
 * - Fork mutexes (via assign_forks())
 *
 * @param philo Pointer to the philosopher structure to configure.
 * @param data Pointer to the shared program data containing all mutexes.
 */
void	assign_mutexes(t_philo *philo, t_data *data)
{
	philo->mutexes.print = &data->mutexes.print_mutex;
	philo->mutexes.term_flag = &data->mutexes.term_mutex;
	philo->mutexes.meal = &data->mutexes.meal_mutexes[philo->id];
	philo->mutexes.full = &data->mutexes.full_mutexes[philo->id];
	philo->mutexes.start = &data->mutexes.start_mutexes[philo->id];
	assign_forks(philo, data);
}

/**
 * @brief Calculates the initial think time delay for a philosopher.
 *
 * This function determines an appropriate delay before a philosopher starts
 * thinking, based on their ID and the program's timing parameters. The delay
 * helps prevent deadlocks and ensures philosophers don't all try to grab
 * forks simultaneously.
 *
 * @param id The philosopher's ID (0-indexed).
 * @param data Pointer to the shared program data containing timing parameters.
 * @return The calculated delay in milliseconds before the philosopher should
 *         start thinking. Returns 0 for philosopher ID 0.
 *
 * @note The delay calculation varies based on:
 *       - Whether there's an even or odd number of philosophers
 *       - The philosopher's position in the sequence
 *       - The configured time_to_eat and time_to_sleep values
 */
t_ms	calculate_initial_think_time(t_count id, t_data *data)
{
	t_ms	delay;

	if (id == 0)
		return (0);
	if (data->input.philo_count % 2 == 0)
		return ((id % 2) * (data->input.time_to_eat * 0.5));
	if (id % 4 == 1)
		delay = (1.5 * data->input.time_to_eat);
	else if (id % 4 == 2)
		delay = data->input.time_to_eat / 2;
	else if (id % 4 == 3)
		delay = data->input.time_to_eat + data->input.time_to_sleep;
	else
		delay = data->input.time_to_eat;
	return (delay);
}
