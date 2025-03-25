/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/25 18:11:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs_philo.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//----------enums----------//

typedef enum e_error
{
	ARGS = 1
}		t_error;

//----------initializations.c----------//

int		initialize_structs(t_program **config);
int		initialize_mutexes(t_program *program);
int		initialize_philos(t_program *program);

//----------validation.c----------//

int		validate_input(int argc, char **argv, t_program *config);

//----------exit.c----------//

void	error_msg(char *msg);
void	exit_philo(char *msg, t_program *config, int exit_code);

//----------cleanup.c----------//

void	cleanup(t_program *config);

#endif