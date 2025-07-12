/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/12 16:05:14 by vpoka            ###   ########.fr       */
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
	t_ms						philo_count;
	t_ms						time_to_die;
	t_ms						time_to_eat;
	t_ms						time_to_sleep;
	t_ms						time_to_think;
	t_ms						meal_limit;
	bool						has_meal_limit;
	t_ms						sim_start_time;
}								t_input;

// docs
typedef struct s_thread
{
	pthread_t					thread;
	bool						initialized;
	struct s_thread				*next;
}								t_thread;

// docs
typedef struct s_mutex
{
	pthread_mutex_t				mutex;
	bool						initialized;
	struct s_mutex				*next;
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
	t_ms						id;
	struct s_input				*input;
	t_ms						last_meal;
	t_ms						meals_eaten;
	bool						*term_flag_ptr;
	struct s_private_mutexes	private_mutexes;
	struct s_global_mutexes		*global_mutexes;
}								t_philo;

// docs
typedef struct s_monitor
{
	pthread_mutex_t				*start;
	struct s_input				*input;
	t_philo						*philos;
	bool						*term_flag_ptr;
	struct s_global_mutexes		*global_mutexes;
}								t_monitor;

// docs
typedef struct s_program
{
	struct s_input				input;
	t_philo						*philos;
	struct s_mutex				mutexes;
	struct s_thread				threads;
	bool						term_flag;
}								t_program;

#endif
