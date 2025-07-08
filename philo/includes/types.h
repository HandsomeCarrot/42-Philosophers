/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:01:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 16:59:39 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

// docs
typedef unsigned long long	t_ms;

// docs
// remove all special errors
// only use error and success?
// maybe death
typedef enum e_error
{
	SUCCESS,
	ERROR,
	TERMINATE
}							t_error;

// docs
typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}							t_mutex_action;

// docs
typedef enum e_philo_state
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEATH
}							t_philo_state;

// docs
typedef enum e_protected_data
{
	LAST_MEAL,
	MEALS_EATEN
}							t_protected_data;

#endif
