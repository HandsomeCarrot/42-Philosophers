/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/20 11:22:18 by vpoka            ###   ########.fr       */
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
	t_ms						time_to_die;		/* Time before death (ms) */
	t_ms						time_to_eat;		/* Time spent eating (ms) */
	t_ms						time_to_sleep;		/* Time spent sleeping (ms) */
	t_ms						time_to_think;		/* Time spent thinking (ms) */
	t_ms						sim_start_time;		/* Simulation start timestamp */
	t_count						philo_count;		/* Number of philosophers */
	t_count						meal_limit;			/* Meal limit (if enabled) */
	bool						has_meal_limit;		/* Whether meal limit is set */
}								t_input;

/**
 * @brief Collection of all mutexes used in the simulation
 * Centralizes mutex management for thread synchronization
 */
typedef struct s_all_mutexes
{
	pthread_mutex_t				print_mutex;		/* Protects console output */
	pthread_mutex_t				term_mutex;			/* Protects termination flag */
	pthread_mutex_t				*start_mutexes;		/* Synchronizes thread start */
	pthread_mutex_t				*fork_mutexes;		/* Protects fork availability */
	pthread_mutex_t				*meal_mutexes;		/* Protects meal timestamps */
	pthread_mutex_t				*full_mutexes;		/* Protects satiation status */
}								t_all_mutexes;

/**
 * @brief Philosopher-specific data arrays
 * Contains arrays for tracking philosopher states and data
 */
typedef struct s_philo_data
{
	t_ms						*last_meals;		/* Last meal timestamps */
	bool						*philo_full;		/* Satiation status array */
	struct s_philo				*philo_data;		/* Individual philo structs */
}								t_philo_data;

/**
 * @brief Thread handles for the simulation
 * Contains pthread_t handles for all simulation threads
 */
typedef struct s_threads
{
	pthread_t					*philos;			/* Philosopher thread array */
	pthread_t					monitor;			/* Monitor thread handle */
}								t_threads;

/**
 * @brief Main data structure containing all simulation components
 * Central structure that holds all simulation state and configuration
 */
typedef struct s_data
{
	struct s_input				input;				/* Command line parameters */
	struct s_all_mutexes		mutexes;			/* All synchronization mutexes */
	struct s_philo_data			philos;				/* Philosopher data arrays */
	struct s_monitor			monitor;			/* Monitor configuration */
	struct s_threads			threads;			/* Thread handles */
	bool						term_flag;			/* Global termination flag */
}								t_data;

#endif
