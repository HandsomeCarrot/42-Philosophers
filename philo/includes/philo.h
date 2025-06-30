/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 01:30:21 by vpoka            ###   ########.fr       */
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

//----------config.c----------//

int	initialize_config(int argc, char **argv);
void	set_simulation_start(t_program *program);
t_ms	get(t_config_data_type data_to_get);

//----------routine.c----------//

void	set_error(t_error error, t_program *program);
t_error	get_error(t_program *program);
void	*routine_start(void *data);

//----------messages.c----------//

char	*get_exec_pattern(void);
void	error_msg(char *msg1, char *msg2);
int	safe_putstr_fd(char *str, int fd, int mutex_state, pthread_mutex_t *mutex);

//----------utils.c----------//

t_ms	ft_atoms(const char *nptr, bool *error);
void	*w_calloc(size_t nmemb, size_t size, t_program *program);
int	ft_strlen(char *str);
int	get_time_in_ms(t_ms *ms_ptr, t_program *program);

//----------mstoa.c----------//

char	*mstoa(t_ms number);

//----------exit.c----------//

void	exit_philo(t_error error, t_program *program);

#endif
