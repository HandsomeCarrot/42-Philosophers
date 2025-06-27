/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 23:12:55 by vpoka            ###   ########.fr       */
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

int				initialize_data(int argc, char **argv, t_program **program);
int				initialize_philos(t_program *program);

//----------config.c----------//

int				initialize_config(int argc, char **argv);
unsigned int	get(int data_to_get);

//----------routine.c----------//

void			set_stop_flag(t_program *program);
void			*routine(t_program *program);

//----------messages.c----------//

char			*get_exec_pattern(void);
void			error_msg(char *msg1, char *msg2);
int				safe_putstr_fd(char *str, int fd, t_program *program);

//----------utils.c----------//

t_ms			ft_atoms(const char *nptr, bool *error);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strlen(char *str);
int				get_time_in_ms(t_ms *ms_ptr, t_program *program);

//----------mstoa.c----------//

char			*mstoa(t_ms number);

//----------exit.c----------//

void			exit_philo(t_program *config, int exit_code);

#endif
