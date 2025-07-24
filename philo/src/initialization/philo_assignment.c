/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_assignment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:45:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:19:36 by vpoka            ###   ########.fr       */
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
 * @brief Calculates initial think time for a philosopher based on their ID.
 *
 * This creates a staggered start pattern where philosophers don't all start
 * thinking at the same time, helping prevent immediate contention for forks.
 * Philosopher 0 starts immediately, others alternate between 0 and 1ms delay.
 *
 * @param id The philosopher's ID number.
 * @return t_ms The initial think time delay in milliseconds (0 or 1).
 */
t_ms	calculate_initial_think_time(t_count id)
{
	if (id == 0)
		return (0);
	return (id % 2);
}
