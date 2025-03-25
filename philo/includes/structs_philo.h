/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_philo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/25 16:14:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_PHILO_H
# define STRUCTS_PHILO_H

# include "philo.h"

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
	pthread_t		*thread;
	struct timeval	*last_meal;
	int				meals_eaten;
}					t_philo;

//----------mutexes----------//

typedef struct s_mutex_data
{
	pthread_mutex_t	**forks;
	pthread_mutex_t	*death;
}					t_mutex_data;

//----------main----------//

typedef struct s_program
{
	t_config		*config;
	t_philo			**philos;
	t_mutex_data	*mutexes;
}					t_program;

#endif