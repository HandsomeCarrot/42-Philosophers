/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:51:14 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 00:07:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

// docs
# define MS_TO_USEC 1000

// docs
// current: 10,000,000 -> 10 seconds in microseconds
# define SLEEP_INTERVAL 10000000

// docs
typedef uint64_t	t_ms; // could be unsigend long long
// docs
typedef uint16_t	t_count; // could be unsigend short

// docs
typedef enum e_error
{
	SUCCESS,
	ERROR,
	TERMINATE
}					t_error;

// docs
typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}					t_mutex_action;

// docs
typedef enum e_philo_state
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEATH
}					t_philo_state;

// docs
typedef enum e_protected_data
{
	LAST_MEAL,
	MEALS_EATEN
}					t_protected_data;

#endif
