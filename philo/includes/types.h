/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:01:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 21:20:53 by vpoka            ###   ########.fr       */
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
}					t_error;

typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}					t_mutex_action;

#endif
