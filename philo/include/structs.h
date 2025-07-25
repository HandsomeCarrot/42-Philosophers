/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 04:27:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "structs_threads.h"

/* ========================================================================== */
/*                            SIMULATION STRUCTURES                          */
/* ========================================================================== */

/**
 * @brief Input parameters for the simulation
 * Contains all timing parameters and limits provided via command line
 */
typedef struct s_input
{
	t_ms						time_to_die;
	t_ms						time_to_eat;
	t_ms						time_to_sleep;
	t_ms						sim_start_time;
	t_count						philo_count;
	t_count						meal_limit;
	bool						has_meal_limit;
}								t_input;

/**
 * @brief Collection of all mutexes used in the simulation
 * Centralizes mutex management for thread synchronization
 */
typedef struct s_all_mutexes
{
	pthread_mutex_t				print_mutex;
	pthread_mutex_t				term_mutex;
	pthread_mutex_t				*start_mutexes;
	pthread_mutex_t				*fork_mutexes;
	pthread_mutex_t				*meal_mutexes;
	pthread_mutex_t				*full_mutexes;
}								t_all_mutexes;

/**
 * @brief Philosopher-specific data arrays
 * Contains arrays for tracking philosopher states and data
 */
typedef struct s_philo_data
{
	t_ms						*last_meals;
	bool						*philo_full;
	struct s_philo				*philo_data;
}								t_philo_data;

/**
 * @brief Thread handles for the simulation
 * Contains pthread_t handles for all simulation threads
 */
typedef struct s_threads
{
	pthread_t					*philos;
	pthread_t					monitor;
}								t_threads;

/**
 * @brief Main data structure containing all simulation components
 * Central structure that holds all simulation state and configuration
 */
typedef struct s_data
{
	struct s_input				input;
	struct s_all_mutexes		mutexes;
	struct s_philo_data			philos;
	struct s_monitor			monitor;
	struct s_threads			threads;
	bool						term_flag;
}								t_data;

#endif
