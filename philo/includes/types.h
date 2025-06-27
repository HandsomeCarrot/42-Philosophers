/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:01:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/28 01:31:43 by vpoka            ###   ########.fr       */
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

// docs
typedef enum e_config_data_type
{
	NBR_OF_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NBR_OF_MEALS,
	HAS_MEAL_LIMIT
}					t_config_data_type;

#endif