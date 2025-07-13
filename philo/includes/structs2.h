/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/13 11:21:26 by vpoka            ###   ########.fr       */
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
	t_ms						philo_count; // change data type
	t_ms						time_to_die;
	t_ms						time_to_eat;
	t_ms						time_to_sleep;
	t_ms						time_to_think; // change data type, maybe even delete
	t_ms						sim_start_time;
	t_ms						meal_limit; // change data type
	bool						has_meal_limit;
}								t_input;

// docs
typedef struct s_thread
{
	struct s_thread				*next;
	pthread_t					thread;
	bool						initialized;
}								t_thread;

// docs
typedef struct s_mutex
{
	struct s_mutex				*next;
	pthread_mutex_t				mutex;
	bool						initialized;
}								t_mutex;

// docs
typedef struct s_global_mutexes
{
	pthread_mutex_t				*print;
	pthread_mutex_t				*term_flag;
}								t_global_mutexes;

// docs
typedef struct s_private_mutexes
{
	pthread_mutex_t				*start;
	pthread_mutex_t				*last_meal;
	pthread_mutex_t				*first_fork;
	pthread_mutex_t				*second_fork;
	pthread_mutex_t				*meals_eaten;
}								t_private_mutexes;

// docs
typedef struct s_philo
{
	struct s_global_mutexes		*global_mutexes;
	struct s_private_mutexes	private_mutexes;
	struct s_input				*input;
	bool						*term_flag_ptr;
	t_ms						meals_eaten;
	t_ms						last_meal;
	t_ms						id;
}								t_philo;

// docs
typedef struct s_monitor
{
	struct s_global_mutexes		*global_mutexes;
	struct s_input				*input;
	pthread_mutex_t				*start;
	t_philo						*philos;
	bool						*term_flag_ptr;
}								t_monitor;

// docs
typedef struct s_program
{
	struct s_thread				threads;
	struct s_mutex				mutexes;
	struct s_input				input;
	t_philo						*philos;
	bool						term_flag;
}								t_program;

#endif
