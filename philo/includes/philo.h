/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/02 14:08:36 by vpoka            ###   ########.fr       */
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

void	initialize_data(int argc, char **argv, t_program **program);

//----------simulation_initialization.c.c----------//

void	start_simulation(t_program *program);

//----------output.c----------//

char	*get_exec_pattern(void);
void	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);

//----------utils.c----------//

t_ms	atoms(const char *nptr, t_program *program);
void	*w_calloc(size_t nmemb, size_t size, t_program *program);
int		ft_strlen(char *str);
void	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);

//----------mstoa.c----------//
// could delete file if I do not tneed the function

char	*mstoa(t_ms number);

//----------exit.c----------//

void	exit_philo(t_error error, t_program *program);

//----------------------------------THREAD-----------------------------------//
//----------thread/*_start.c----------//

void	*routine_start(void *data);

//----------thread/*_utils.c----------//

int		get_time_in_ms(t_ms *ms_ptr, t_mutexes *mutexes);
void	set_error(t_error error, int *error_flag, t_mutexes *mutexes);
int		get_error(int *error_flag, t_mutexes *mutexes);

#endif
