/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 19:35:31 by vpoka            ###   ########.fr       */
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

//------------------------------INITIALIZATION-------------------------------//

t_error	initialize_data(int argc, char **argv, t_data **data_ptr);
t_error	proccess_input(bool meal_limit, char **argv, t_data *data);
t_error	create_mutexes(t_data *data);
t_error	create_philo_data(t_data *data);
void	assign_monitor_data(t_data *data);

//------------------------------SIMULATION-------------------------------//

t_error	start_simulation(t_data *data);

// philos

void	*philo_start(void *data);

// monitor

void	*monitor_start(void *data);

//------------------------------UTILS-------------------------------//

// output

t_error	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);
t_error	print_state(t_philo_state state, t_ms *timestamp, t_philo *philo);
char	*get_exec_pattern(void);

// memory

void	*w_calloc(size_t nmemb, size_t size);

// mutexes

t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);

// thread helpers

void	set_termination_flag(bool *term_flag_ptr, pthread_mutex_t *mutex);
bool	termination_requested(bool *term_flag_ptr, pthread_mutex_t *mutex);
t_error	wait_for_start(t_input *input, pthread_mutex_t *mutex);

// time

t_error	get_current_time_ms(t_ms *ms_ptr);
t_error	get_elapsed_time(t_ms *ms_ptr, t_input *input);

//------------------------------CLEANUP-------------------------------//

t_error	erase_data(t_data *data);
t_error	join_all_threads(t_data *data);
t_error	free_philo_data(t_data *data);

// mutexes

t_error	destroy_mutex_array(t_count count, pthread_mutex_t **mutex_array);
t_error	destroy_all_mutexes(t_data *data);

#endif
