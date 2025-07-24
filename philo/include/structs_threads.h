/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_threads.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:16:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 15:55:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_THREADS_H
# define STRUCTS_THREADS_H

# include "types.h"
# include <pthread.h>
# include <stdbool.h>

/* ========================================================================== */
/*                           THREAD-SPECIFIC STRUCTURES                      */
/* ========================================================================== */

/**
 * @brief Mutex collection for individual philosopher threads
 * Contains pointers to all mutexes a philosopher needs to access
 */
typedef struct s_philo_mutexes
{
	pthread_mutex_t				*print;				/* Output synchronization */
	pthread_mutex_t				*term_flag;			/* Termination flag access */
	pthread_mutex_t				*first_fork;		/* First fork to acquire */
	pthread_mutex_t				*second_fork;		/* Second fork to acquire */
	pthread_mutex_t				*meal;				/* Meal timestamp protection */
	pthread_mutex_t				*full;				/* Satiation status protection */
	pthread_mutex_t				*start;				/* Synchronization at start */
}								t_philo_mutexes;

/**
 * @brief Individual philosopher thread data
 * Contains all data and state needed for a philosopher thread
 * Note: meals_eaten is tracked locally within each thread
 */
typedef struct s_philo
{
	struct s_philo_mutexes		mutexes;			/* Mutex pointers */
	struct s_input				*input;				/* Simulation parameters */
	bool						*term_flag;			/* Global termination flag */
	t_ms						*last_meal;			/* Timestamp of last meal */
	bool						*full;				/* Whether philosopher is full */
	t_count						id;					/* Philosopher unique ID */
	t_count						meals_eaten;		/* Local meal counter */
	t_ms						initial_think_time;	/* Initial thinking duration */
}								t_philo;

/**
 * @brief Philosopher data collection for monitor thread
 * Contains arrays and pointers the monitor needs to check all philosophers
 */
typedef struct s_monitor_philo_data
{
	pthread_mutex_t				*meal_mutexes;		/* Meal timestamp mutexes */
	t_ms						*last_meals;		/* Last meal timestamp array */
	pthread_mutex_t				*full_mutexes;		/* Satiation status mutexes */
	bool						*philo_full;		/* Satiation status array */
	struct s_philo				*philo_data;		/* Philosopher struct array */
}								t_monitor_philo_data;

/**
 * @brief Monitor thread data structure
 * Contains all data needed for the monitor thread to oversee simulation
 */
typedef struct s_monitor
{
	struct s_input				*input;				/* Simulation parameters */
	struct s_monitor_philo_data	philos;				/* Philosopher monitoring data */
	pthread_mutex_t				*term_mutex;		/* Termination flag mutex */
	bool						*term_flag;			/* Global termination flag */
	pthread_mutex_t				*print_mutex;		/* Output synchronization */
	pthread_mutex_t				*start_mutex;		/* Start synchronization */
}								t_monitor;

#endif
