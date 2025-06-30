/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:27:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 14:59:08 by vpoka            ###   ########.fr       */
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
	bool				has_meal_limit;
	t_ms				meal_limit;
	t_ms				sim_start_time;
}						t_input;

//----------universal-mutexes----------//

// docs
typedef struct s_mutexes
{
	pthread_mutex_t		*stop; // alloced
	pthread_mutex_t		*print; // alloced
	pthread_mutex_t		**forks; // alloced pointer and pointers in pointer
}						t_mutexes;

//----------philosopher-data----------//

// docs
typedef struct s_philo
{
	t_ms				id;
	t_ms				last_meal;
	t_ms				meals_eaten;
	pthread_t			thread;
	int					*global_error;
	struct s_input		*input;
	struct s_mutexes	*mutexes;
}						t_philo;

//----------main----------//

// docs
typedef struct s_program // alloced
{
	t_ms				philo_count;
	int					error;
	t_philo				*philos; // alloced
	struct s_input		input;
	struct s_mutexes	mutexes;
}						t_program;

#endif
