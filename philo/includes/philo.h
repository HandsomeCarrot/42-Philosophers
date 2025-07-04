/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/04 19:17:14 by vpoka            ###   ########.fr       */
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

//----------output.c----------//

char	*get_exec_pattern(void);
void	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);

//----------utils.c----------//

t_error	atoms(const char *str, t_ms *result);
void	*w_calloc(size_t nmemb, size_t size);
int		ft_strlen(char *str);
t_error	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);

//----------mstoa.c----------//
// could delete file if I do not tneed the function

char	*mstoa(t_ms number);

//----------------------------------THREAD-----------------------------------//
//----------thread/*_start.c----------//

void	*routine_start(void *data);

//----------thread/*_utils.c----------//

t_error	get_time_in_ms(t_ms *ms_ptr, t_mutexes *mutexes);
void	terminate_threads(bool *term_flag_ptr, t_mutexes *mutexes);
bool	is_termination_requested(bool *term_flag_ptr, t_mutexes *mutexes);

//----------------------------------CLEANUP-----------------------------------//
//----------cleanup.c----------//

t_error	cleanup_program(bool set_term_flag, t_program *program);

//----------thread_cleanup.c----------//

t_error	join_all_threads(t_program *program);

//----------mutex_cleanup.c----------//

t_error	destroy_all_mutexes(t_program *program);

#endif
