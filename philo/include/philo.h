/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 17:45:46 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "types.h"
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* ========================================================================== */
/*                                INITIALIZATION                             */
/* ========================================================================== */

/**
 * @brief Initialize all data structures for the simulation
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @param data_ptr Pointer to data structure pointer to initialize
 * @return SUCCESS on success, ERROR on failure
 */
t_error	initialize_data(int argc, char **argv, t_data **data_ptr);

/**
 * @brief Process and validate command line input parameters
 * @param meal_limit Whether meal limit was provided
 * @param argv Array of command line arguments
 * @param data Data structure to populate with input values
 * @return SUCCESS on success, ERROR on failure
 */
t_error	proccess_input(bool meal_limit, char **argv, t_data *data);

/**
 * @brief Create and initialize all mutex structures
 * @param data Data structure containing mutex information
 * @return SUCCESS on success, ERROR on failure
 */
t_error	create_mutexes(t_data *data);

/**
 * @brief Create and initialize philosopher data structures
 * @param data Main data structure containing simulation parameters
 * @return SUCCESS on success, ERROR on failure
 */
t_error	create_philo_data(t_data *data);

/**
 * @brief Assign data pointers to monitor structure
 * @param data Main data structure to assign from
 */
void	assign_monitor_data(t_data *data);

/**
 * @brief Assign mutex pointers to philosopher structure
 * @param philo Philosopher structure to assign mutexes to
 * @param data Main data structure containing mutexes
 */
void	assign_mutexes(t_philo *philo, t_data *data);

/**
 * @brief Calculate initial think time for philosopher to prevent deadlock
 * @param id Philosopher ID
 * @return Initial think time in milliseconds
 */
t_ms	calculate_initial_think_time(t_count id);

/* ========================================================================== */
/*                                 SIMULATION                                */
/* ========================================================================== */

/**
 * @brief Start the philosopher simulation with threads
 * @param data Main data structure containing all simulation parameters
 * @return SUCCESS on success, ERROR on failure
 */
t_error	start_simulation(t_data *data);

/* -------------------------------- PHILOS --------------------------------- */

/**
 * @brief Main philosopher thread function
 * @param data Philosopher data cast to void pointer
 * @return Thread termination value
 */
void	*philo_start(void *data);

/**
 * @brief Handle fork acquisition and release for philosopher
 * @param action LOCK to acquire forks, UNLOCK to release forks
 * @param data Philosopher data structure
 * @return SUCCESS on success, ERROR on failure
 */
t_error	philo_forks(t_mutex_action action, t_philo *data);

/**
 * @brief Execute eating action for philosopher
 * @param data Philosopher data structure
 * @return SUCCESS on success, ERROR or TERMINATE on failure
 */
t_error	philo_eat(t_philo *data);

/**
 * @brief Execute sleeping action for philosopher
 * @param data Philosopher data structure
 * @return SUCCESS on success, ERROR or TERMINATE on failure
 */
t_error	philo_sleep(t_philo *data);

/**
 * @brief Execute thinking action for philosopher
 * @param data Philosopher data structure
 * @return SUCCESS on success, ERROR or TERMINATE on failure
 */
t_error	philo_think(t_philo *data);

/* ------------------------------- MONITOR --------------------------------- */

/**
 * @brief Main monitor thread function to check for death/completion
 * @param data Monitor data cast to void pointer
 * @return Thread termination value
 */
void	*monitor_start(void *data);

/* ========================================================================== */
/*                                   UTILS                                   */
/* ========================================================================== */

/* -------------------------------- OUTPUT --------------------------------- */

/**
 * @brief Print error message to stderr
 * @param msg1 First part of error message
 * @param msg2 Second part of error message
 * @return ERROR always
 */
t_error	error_msg(char *msg1, char *msg2);

/**
 * @brief Thread-safe string output to file descriptor
 * @param str String to output
 * @param fd File descriptor to write to
 * @param print_mutex Mutex for thread-safe printing
 */
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);

/**
 * @brief Print philosopher state change with timestamp
 * @param state New state of philosopher
 * @param timestamp Pointer to store timestamp
 * @param philo Philosopher data structure
 * @return SUCCESS on success, ERROR on failure
 */
t_error	print_state(t_philo_state state, t_ms *timestamp, t_philo *philo);

/**
 * @brief Get execution pattern string for debugging
 * @return Pointer to execution pattern string
 */
char	*get_exec_pattern(void);

/* ------------------------------- MEMORY ---------------------------------- */

/**
 * @brief Wrapper for calloc with error handling
 * @param nmemb Number of elements to allocate
 * @param size Size of each element
 * @return Pointer to allocated memory or NULL on failure
 */
void	*w_calloc(size_t nmemb, size_t size);

/* ------------------------------- MUTEXES --------------------------------- */

/**
 * @brief Wrapper for mutex operations with error handling
 * @param action LOCK or UNLOCK operation
 * @param mutex Mutex to operate on
 * @return SUCCESS on success, ERROR on failure
 */
t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);

/* ------------------------------- THREADS --------------------------------- */

/**
 * @brief Set termination flag in thread-safe manner
 * @param term_flag_ptr Pointer to termination flag
 * @param mutex Mutex protecting the flag
 */
void	set_termination_flag(bool *term_flag_ptr, pthread_mutex_t *mutex);

/**
 * @brief Check if termination was requested in thread-safe manner
 * @param term_flag_ptr Pointer to termination flag
 * @param mutex Mutex protecting the flag
 * @return true if termination requested, false otherwise
 */
bool	termination_requested(bool *term_flag_ptr, pthread_mutex_t *mutex);

/**
 * @brief Wait for simulation start signal
 * @param mutex Start mutex to wait on
 * @return SUCCESS on success, ERROR on failure
 */
t_error	wait_for_start(pthread_mutex_t *mutex);

/* -------------------------------- TIME ----------------------------------- */

/**
 * @brief Get current time in milliseconds
 * @param ms_ptr Pointer to store current time
 * @return SUCCESS on success, ERROR on failure
 */
t_error	get_current_time_ms(t_ms *ms_ptr);

/**
 * @brief Calculate elapsed time from start time
 * @param ms_ptr Pointer to store elapsed time
 * @param start_time Starting time reference
 * @return SUCCESS on success, ERROR on failure
 */
t_error	get_elapsed_time(t_ms *ms_ptr, t_ms start_time);

/**
 * @brief Precise sleep implementation for small time intervals
 * @param sleep_time_ms Time to sleep in milliseconds
 * @return SUCCESS on success, ERROR on failure
 */
t_error	precise_sleep(t_ms sleep_time_ms);

/**
 * @brief Thread sleep with termination checking
 * @param time Time to sleep in milliseconds
 * @param philo Philosopher data for termination checking
 * @return SUCCESS on success, ERROR or TERMINATE on failure
 */
t_error	thread_sleep(t_ms time, t_philo *philo);

/* ------------------------------- STRINGS --------------------------------- */

/**
 * @brief Calculate length of string
 * @param str String to measure
 * @return Length of string
 */
int		ft_strlen(char *str);

/* ========================================================================== */
/*                                  CLEANUP                                  */
/* ========================================================================== */

/**
 * @brief Clean up all allocated data and resources
 * @param data Main data structure to clean up
 * @return SUCCESS on success, ERROR on failure
 */
t_error	erase_data(t_data *data);

/**
 * @brief Join all active threads
 * @param data Data structure containing thread information
 * @return SUCCESS on success, ERROR on failure
 */
t_error	join_all_threads(t_data *data);

/**
 * @brief Free philosopher data arrays
 * @param data Data structure containing philosopher arrays
 * @return SUCCESS on success, ERROR on failure
 */
t_error	free_philo_data(t_data *data);

/* ------------------------------- MUTEXES --------------------------------- */

/**
 * @brief Destroy array of mutexes
 * @param count Number of mutexes in array
 * @param mutex_array Array of mutexes to destroy
 * @return SUCCESS on success, ERROR on failure
 */
t_error	destroy_mutex_array(t_count count, pthread_mutex_t **mutex_array);

/**
 * @brief Destroy all mutexes in data structure
 * @param data Data structure containing mutexes to destroy
 * @return SUCCESS on success, ERROR on failure
 */
t_error	destroy_all_mutexes(t_data *data);

#endif
