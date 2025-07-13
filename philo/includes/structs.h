/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/13 12:39:56 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "types.h"
# include <pthread.h>
# include <stdbool.h>

//----------user-input----------//

// docs
typedef struct s_input
{
	t_ms					time_to_die;
	t_ms					time_to_eat;
	t_ms					time_to_sleep;
	t_ms					time_to_think;
	t_ms					philo_count;
	t_ms					meal_limit;
	bool					has_meal_limit;
	t_ms					sim_start_time;
}							t_input;

//----------mutexes----------//

// docs
typedef struct s_mutexes
{
	pthread_mutex_t			*term_flag;
	pthread_mutex_t			*print;
	pthread_mutex_t			**forks;
	pthread_mutex_t			**last_meal;
	pthread_mutex_t			**meals_eaten;
	pthread_mutex_t			**start_mutexes;
}							t_mutexes;

// docs
typedef struct s_philo_mutexes
{
	pthread_mutex_t			*start;
	pthread_mutex_t			*print;
	pthread_mutex_t			*term_flag;
	pthread_mutex_t			*last_meal;
	pthread_mutex_t			*meals_eaten;
	pthread_mutex_t			*first_fork;
	pthread_mutex_t			*second_fork;
}							t_philo_mutexes;

//----------philosopher-data----------//

// docs
typedef struct s_philo
{
	struct s_philo_mutexes	mutexes;
	struct s_input			*input;
	bool					*term_flag_ptr;
	pthread_t				thread;
	t_ms					meals_eaten;
	t_ms					last_meal;
	t_ms					id;
}							t_philo;

//----------main----------//

// docs
typedef struct s_program
{
	bool					term_flag;
	pthread_t				monitor_thread;
	t_philo					*philos;
	struct s_input			input;
	struct s_mutexes		mutexes;
}							t_program;

#endif
