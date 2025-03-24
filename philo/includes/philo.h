/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 17:18:38 by vpoka            ###   ########.fr       */
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

typedef struct s_params
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	int	start_time;
}		t_params;

//----------initializations.c----------//

int		initialize_structs(t_params **config);

//----------validation.c----------//

int		validate_input(int argc, char **argv, t_params *config);

//----------exit.c----------//

void	error_msg(char *msg);
void	exit_philo(char *msg, t_params *config, int exit_code);

//----------cleanup.c----------//

void	cleanup(t_params *config);

#endif