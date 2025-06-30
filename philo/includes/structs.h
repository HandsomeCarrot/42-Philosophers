/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 01:24:08 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "types.h"
# include <pthread.h>
# include <stdbool.h>

//----------user-input----------//

// docs
typedef struct s_config
{
	t_ms				number_of_philos;
	t_ms				time_to_die;
	t_ms				time_to_eat;
	t_ms				time_to_sleep;
	t_ms				number_of_meals;
	t_ms				sim_start_time;
	bool				has_meal_limit;
}						t_config;

//----------philosopher-data----------//

// docs
typedef struct s_philo
{
	t_ms				id;
	t_ms				last_meal;
	t_ms				meals_eaten;
	struct s_mutexes	*mutexes;
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
	pthread_t			*philos;
	int					error;
}						t_program;

#endif