/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_philo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/25 18:31:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_PHILO_H
# define STRUCTS_PHILO_H

# include "philo.h"

//----------enums----------//

typedef enum e_stop
{
	ERROR = 1,
	NORMAL,
	DEATH
}		t_stop;


//----------user-input----------//

typedef struct s_config
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_meals;
}					t_config;

//----------philosopher-data----------//

typedef struct s_philo
{
	struct timeval	*last_meal;
	pthread_t		*thread;
	unsigned int	meals_eaten;
}					t_philo;

//----------mutexes----------//

typedef struct s_mutex_data
{
	pthread_mutex_t	**forks;
	pthread_mutex_t	*stop;
}					t_mutex_data;

//----------main----------//

typedef struct s_program
{
	t_config		*config;
	t_philo			**philos;
	t_mutex_data	*mutexes;
	int				stop_threads;
}					t_program;

#endif