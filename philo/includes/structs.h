/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/11 18:53:54 by vpoka            ###   ########.fr       */
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
	t_ms				time_to_die;
	t_ms				time_to_eat;
	t_ms				time_to_sleep;
	t_ms				time_to_think;
	t_ms				philo_count;
	t_ms				meal_limit;
	bool				has_meal_limit;
	t_ms				sim_start_time;
}						t_input;

//----------universal-mutexes----------//

// docs
typedef struct s_mutexes
{
	pthread_mutex_t		*term_flag;
	pthread_mutex_t		*print;
	pthread_mutex_t		**forks;
	pthread_mutex_t		**last_meal;
	pthread_mutex_t		**meals_eaten;
	pthread_mutex_t		**start_mutexes;
}						t_mutexes;

//----------philosopher-data----------//

// docs
typedef struct s_philo
{
	t_ms				id;
	t_ms				last_meal;
	t_ms				meals_eaten;
	pthread_t			thread;
	bool				*term_flag_ptr;
	struct s_input		*input;
	struct s_mutexes	*mutexes;
}						t_philo;

//----------main----------//

// docs
typedef struct s_program
{
	bool				term_flag;
	pthread_t			monitor_thread;
	t_philo				*philos;
	struct s_input		input;
	struct s_mutexes	mutexes;
}						t_program;

#endif
