/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 13:55:47 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

//----------user-input----------//

typedef struct s_config
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_meals;
	bool			eat_to_death;
}					t_config;

//----------philosopher-data----------//

typedef struct s_philo
{
	struct timeval	*last_meal;
	pthread_t		*thread;
	unsigned int	meals_eaten;
	struct s_philo	*next;
	struct s_philo	*previous;
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
	int				stop_flag;
}					t_program;

#endif