/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_threads.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:16:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/22 16:59:02 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_THREADS_H
# define STRUCTS_THREADS_H

# include "types.h"
# include <pthread.h>
# include <stdbool.h>

// docs
typedef struct s_philo_mutexes
{
	pthread_mutex_t			*print;
	pthread_mutex_t			*term_flag;
	pthread_mutex_t			*first_fork;
	pthread_mutex_t			*second_fork;
	pthread_mutex_t			*meal;
	pthread_mutex_t			*full;
	pthread_mutex_t			*start;
}							t_philo_mutexes;

// docs
// meals_eaten will be a local variable (maybe static)
typedef struct s_philo
{
	struct s_philo_mutexes	mutexes;
	struct s_input			*input;
	bool					*term_flag;
	t_ms					*last_meal;
	bool					*full;
	t_count					id;
}							t_philo;

// docs
typedef struct s_monitor_philo_data
{
	pthread_mutex_t				*meal_mutexes;
	t_ms						*last_meals;
	pthread_mutex_t				*full_mutexes;
	bool						*philo_full;
}								t_monitor_philo_data;

// docs
typedef struct s_monitor
{
	struct s_input				*input;
	struct s_monitor_philo_data	philos;
	pthread_mutex_t				*term_mutex;
	bool						*term_flag;
	pthread_mutex_t				*print_mutex;
	pthread_mutex_t				*start_mutex;
}								t_monitor;

#endif