/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 16:22:43 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//----------enums----------//

typedef enum e_error
{
	ARGS = 1
}		t_error;

//----------enums----------//

typedef struct s_config
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	int	start_time;
}		t_config;

//----------initializations.c----------//

int		initialize_structs(t_config **config);

//----------validation.c----------//

int		validate_input(int argc, char **argv, t_config *config);

//----------exit.c----------//

void	error_msg(char *msg);
void	exit_philo(char *msg, t_config *config, int exit_code);

//----------cleanup.c----------//

void	cleanup(t_config *config);

#endif