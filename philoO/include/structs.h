/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/15 13:12:04 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "types.h"
# include <pthread.h>
# include <stdbool.h>

// docs
typedef struct s_input
{
	t_ms						time_to_die;
	t_ms						time_to_eat;
	t_ms						time_to_sleep;
	t_ms						time_to_think;
	t_ms						sim_start_time;
	t_ms						philo_count; // change data type
	t_ms						meal_limit; // change data type
	bool						has_meal_limit;
}								t_input;

// docs
// meals_eaten will be a local variable (maybe static)
typedef struct s_philo
{
	pthread_mutex_t	*start_mutex;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*meal_mutex;
	t_ms			*last_meal;
	pthread_mutex_t	*full_mutex;
	bool			*full;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*term_mutex;
	bool			*term_flag;
	struct s_input	*input;
	t_ms			id;
}	t_philo;

// docs
typedef struct s_monitor
{
	struct s_input	*input;
	pthread_mutex_t	*meal_mutexes;
	t_ms			*last_meals;
	pthread_mutex_t	*full_mutexes;
	bool			*philo_full;
	pthread_mutex_t	*start_mutex;
	pthread_mutex_t	*term_mutex;
	bool			*term_flag;
	pthread_mutex_t	*print_mutex;
}	t_monitor;

// docs
typedef struct s_all_mutexes
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	term_mutex;
	pthread_mutex_t	*start_mutexs;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*meal_mutexes;
	pthread_mutex_t	*full_mutexes;
}	t_all_mutexes;

// docs
typedef struct s_philo_data
{
	struct s_philo	*philo_data;
	t_ms			*last_meals;
	bool			*philo_full;
}	t_philo_data;

// docs
typedef struct s_data
{
	struct s_input			input;
	struct s_all_mutexes	mutexes;
	struct s_philo_data		philos;
	struct s_monitor		monitor;
	bool					term_flag;
}	t_data;

#endif
