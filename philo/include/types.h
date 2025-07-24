/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:51:14 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 00:51:11 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

/* ========================================================================== */
/*                               CONSTANTS                                   */
/* ========================================================================== */

/**
 * @brief Conversion factor from milliseconds to microseconds
 * Used for precise timing calculations in usleep()
 */
# define MS_TO_USEC			1000

/**
 * @brief Sleep interval for thread sleep monitoring in microseconds
 * Current value: 10,000 microseconds = 10 milliseconds
 * Used to check termination conditions during long sleeps
 */
# define SLEEP_INTERVAL		10000

/* ========================================================================== */
/*                               DATA TYPES                                  */
/* ========================================================================== */

/**
 * @brief Time type in milliseconds
 * Used for all time-related calculations in the simulation
 */
typedef uint64_t	t_ms;

/**
 * @brief Count type for philosophers and meals
 * Used for philosopher IDs, meal counts, and array indices
 */
typedef uint16_t	t_count;

/* ========================================================================== */
/*                               ENUMERATIONS                                */
/* ========================================================================== */

/**
 * @brief Error codes for function return values
 * SUCCESS: Operation completed successfully
 * ERROR: Operation failed due to error
 * TERMINATE: Operation terminated due to simulation end
 */
typedef enum e_error
{
	SUCCESS,
	ERROR,
	TERMINATE
}					t_error;

/**
 * @brief Mutex operations for thread synchronization
 * LOCK: Acquire mutex lock
 * UNLOCK: Release mutex lock
 */
typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}					t_mutex_action;

/**
 * @brief Philosopher states for simulation logging
 * FORK: Philosopher has taken a fork
 * EATING: Philosopher is eating
 * SLEEPING: Philosopher is sleeping
 * THINKING: Philosopher is thinking
 * DEATH: Philosopher has died
 */
typedef enum e_philo_state
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEATH
}					t_philo_state;

#endif
