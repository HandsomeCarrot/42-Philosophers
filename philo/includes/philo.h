/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 17:22:04 by vpoka            ###   ########.fr       */
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

//----------initializations.c----------//

void	initialize_data(int argc, char **argv, t_program **program);
void	start_simulation(t_program *program);

//----------routine.c----------//

void	set_error(t_error error, int *error_flag, t_mutexes *mutexes);
void	get_error(int *error_flag, t_mutexes *mutexes);
void	*routine_start(void *data);

//----------messages.c----------//

char	*get_exec_pattern(void);
void	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);

//----------utils.c----------//

t_ms	atoms(const char *nptr, t_program *program);
void	*w_calloc(size_t nmemb, size_t size, t_program *program);
int		ft_strlen(char *str);
int		get_time_in_ms(t_ms *ms_ptr, pthread_mutex_t *mutex);
void	w_mutex(t_mutex_action action, pthread_mutex_t *mutex);

//----------mstoa.c----------//

char	*mstoa(t_ms number);

//----------exit.c----------//

void	exit_philo(t_error error, t_program *program);

#endif
