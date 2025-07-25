/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 19:16:48 by vpoka            ###   ########.fr       */
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

t_error	initialize_data(int argc, char **argv, t_data **data_ptr);
t_error	proccess_input(bool meal_limit, char **argv, t_data *data);
t_error	create_mutexes(t_data *data);
t_error	create_philo_data(t_data *data);
void	assign_monitor_data(t_data *data);
void	assign_mutexes(t_philo *philo, t_data *data);
t_ms	calculate_initial_think_time(t_count id, t_data *data);

/* ========================================================================== */
/*                                 SIMULATION                                */
/* ========================================================================== */

t_error	start_simulation(t_data *data);

/* -------------------------------- PHILOS --------------------------------- */

void	*philo_start(void *data);
t_error	philo_forks(t_mutex_action action, t_philo *data);
t_error	philo_eat(t_philo *data);
t_error	philo_sleep(t_philo *data);
t_error	philo_think(t_philo *data);

/* ------------------------------- MONITOR --------------------------------- */

void	*monitor_start(void *data);

/* ========================================================================== */
/*                                   UTILS                                   */
/* ========================================================================== */

/* -------------------------------- OUTPUT --------------------------------- */

t_error	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);
t_error	print_state(t_philo_state state, t_ms *timestamp, t_philo *philo);
char	*get_exec_pattern(void);

/* ------------------------------- MEMORY ---------------------------------- */

void	*w_calloc(size_t nmemb, size_t size);

/* ------------------------------- MUTEXES --------------------------------- */

t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);

/* ------------------------------- THREADS --------------------------------- */

void	set_termination_flag(bool *term_flag_ptr, pthread_mutex_t *mutex);
bool	termination_requested(bool *term_flag_ptr, pthread_mutex_t *mutex);
t_error	wait_for_start(pthread_mutex_t *mutex);

/* -------------------------------- TIME ----------------------------------- */

t_error	get_current_time_ms(t_ms *ms_ptr);
t_error	get_elapsed_time(t_ms *ms_ptr, t_ms start_time);
t_error	precise_sleep(t_ms sleep_time_ms);
t_error	thread_sleep(t_ms time, t_philo *philo);

/* ------------------------------- STRINGS --------------------------------- */

int		ft_strlen(char *str);

/* ========================================================================== */
/*                                  CLEANUP                                  */
/* ========================================================================== */

t_error	erase_data(t_data *data);
t_error	join_all_threads(t_data *data);
t_error	free_philo_data(t_data *data);

/* ------------------------------- MUTEXES --------------------------------- */

t_error	destroy_mutex_array(t_count count, pthread_mutex_t **mutex_array,
			bool **init_tracker);
t_error	destroy_all_mutexes(t_data *data);

#endif
