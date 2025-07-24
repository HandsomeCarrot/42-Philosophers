/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_threads.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:16:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 00:50:23 by vpoka            ###   ########.fr       */
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
	pthread_mutex_t				*print;
	pthread_mutex_t				*term_flag;
	pthread_mutex_t				*first_fork;
	pthread_mutex_t				*second_fork;
	pthread_mutex_t				*meal;
	pthread_mutex_t				*full;
	pthread_mutex_t				*start;
}								t_philo_mutexes;

/**
 * @brief Individual philosopher thread data
 * Contains all data and state needed for a philosopher thread
 * Note: meals_eaten is tracked locally within each thread
 */
typedef struct s_philo
{
	struct s_philo_mutexes		mutexes;
	struct s_input				*input;
	bool						*term_flag;
	t_ms						*last_meal;
	bool						*full;
	t_count						id;
	t_count						meals_eaten;
	t_ms						initial_think_time;
}								t_philo;

/**
 * @brief Philosopher data collection for monitor thread
 * Contains arrays and pointers the monitor needs to check all philosophers
 */
typedef struct s_monitor_philo_data
{
	pthread_mutex_t				*meal_mutexes;
	t_ms						*last_meals;
	pthread_mutex_t				*full_mutexes;
	bool						*philo_full;
	struct s_philo				*philo_data;
}								t_monitor_philo_data;

/**
 * @brief Monitor thread data structure
 * Contains all data needed for the monitor thread to oversee simulation
 */
typedef struct s_monitor
{
	struct s_input				*input;
	struct s_monitor_philo_data	philos;
	pthread_mutex_t				*term_mutex;
	bool						*term_flag;
	pthread_mutex_t				*print_mutex;
	pthread_mutex_t				*start_mutex;
}								t_monitor;

#endif
