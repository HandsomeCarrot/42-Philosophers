/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 16:20:31 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "types.h"
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//-----------------------------------ROOT------------------------------------//
//----------initialization.c----------//

t_error	initialize_data(int argc, char **argv, t_program **program);

//----------simulation_initialization.c.c----------//

t_error	start_simulation(t_program *prografm);

//-----------------------------------UTILS------------------------------------//
//----------memory_utils.c----------//

void	*w_calloc(size_t nmemb, size_t size);

//----------mutex_utils.c----------//

t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);
t_error	all_forks(t_mutex_action action, t_program *program);

//----------output_utils.c----------//

void	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);
t_error	print_state(t_philo_state state, t_ms timestamp, t_philo *philo);
char	*get_exec_pattern(void);

//----------string_utils.c----------//

char	*mstoa(t_ms number);
t_error	atoms(const char *str, t_ms *result);
int		ft_strlen(char *str);

//----------thread_helpers.c----------//

void	terminate_threads(bool *term_flag_ptr, t_mutexes *mutexes);
bool	is_termination_requested(bool *term_flag_ptr, t_mutexes *mutexes);
void	*thread_error(bool *term_flag_ptr, t_mutexes *mutexes);
t_error	wait_for_start(pthread_mutex_t *mutex);

//----------time_utils.c----------//

t_error	get_time_in_ms(t_ms *ms_ptr, t_mutexes *mutexes);
t_error	get_time_since_start(t_ms *ms_ptr, t_input *input, t_mutexes *mutexes);

//----------------------------------THREADS-----------------------------------//
//----------thread_philosophers.c----------//

void	*philo_start(void *data);

//----------thread_monitoring.c----------//

void	*monitor_start(void *data);

//----------------------------------CLEANUP-----------------------------------//
//----------cleanup.c----------//

t_error	cleanup_program(bool set_term_flag, t_program *program);

//----------thread_cleanup.c----------//

t_error	join_all_threads(t_program *program);

//----------mutex_cleanup.c----------//

t_error	destroy_all_mutexes(t_program *program);

#endif
