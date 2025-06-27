/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 16:28:20 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//----------enums----------//

# define SUCCESS 0
# define ERROR 1

typedef enum e_config_data_type
{
	NBR_OF_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NBR_OF_MEALS
}				t_config_data_type;

typedef enum e_stop
{
	STOP_ERROR = 1,
	STOP_NORMAL,
	STOP_DEATH
}				t_stop;

//----------initializations.c----------//

int				initialize_structs(t_program **program);
int				initialize_universal_mutexes(t_mutexes *mutexes);
int				initialize_philos(t_program *program);

//----------config.c----------//

int				initialize_config(int argc, char **argv);
unsigned int	get(int data_to_get);
bool			has_meal_limit(void);

//----------routine.c----------//

void			set_stop_flag(t_program *program);
void			*routine(t_program *program);

//----------messages.c----------//

char			*get_exec_pattern(void);
void			error_msg(char *msg1, char *msg2);

//----------utils.c----------//

unsigned int	ft_atoui(const char *nptr, int *error);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strlen(char *str);

//----------exit.c----------//

void			exit_philo(t_program *config, int exit_code);

#endif
