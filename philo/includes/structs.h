/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 16:06:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

//----------user-input----------//

// docs
typedef struct s_config
{
	unsigned int		number_of_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		number_of_meals;
	bool				simulate_until_death;
}						t_config;

//----------philosopher-data----------//

// docs
typedef struct s_philo
{
	pthread_mutex_t		*fork;
	pthread_t			*thread;
	struct timeval		*last_meal;
	unsigned int		meals_eaten;
}						t_philo;

//----------universal-mutexes----------//

// docs
typedef struct s_mutexes
{
	pthread_mutex_t		*stop;
	pthread_mutex_t		*print;
	pthread_mutex_t		**forks;
}						t_mutexes;

//----------main----------//

// docs
typedef struct s_program
{
	struct s_mutexes	*mutexes;
	struct s_philo		**philos;
	int					stop_flag;
}						t_program;

#endif