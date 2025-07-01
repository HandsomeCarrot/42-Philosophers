/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:01:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 13:48:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

// docs
typedef uint64_t	t_ms;

// docs
typedef enum e_error
{
	SUCCESS,
	ERROR,
	DEATH
}					t_error;

typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}					t_mutex_action;

#endif