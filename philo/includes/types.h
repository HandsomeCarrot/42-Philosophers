/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:01:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/03 23:35:20 by vpoka            ###   ########.fr       */
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
	ERR_ARG,
	ERR_ALLOC,
	ERR_THREAD,
	ERR_MUTEX,
	ERR_SYNC,
	ERR_TIME,
	ERR_INIT,
	ERR_JOIN,
	ERR_DESTROY,
	ERR_CREATE,
	DEATH
}					t_error;

typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}					t_mutex_action;

#endif
