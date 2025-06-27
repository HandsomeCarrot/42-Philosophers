/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:01:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/27 18:02:38 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBR_DEFS_H
# define NBR_DEFS_H

# include <stdint.h>

// docs
# define SUCCESS 0
// docs
# define ERROR 1

// docs
typedef uint64_t	t_ms;

// docs
typedef enum e_config_data_type
{
	NBR_OF_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NBR_OF_MEALS,
	HAS_MEAL_LIMIT,
	SIM_START
}					t_config_data_type;

// docs
typedef enum e_stop
{
	STOP_ERROR = 1,
	STOP_NORMAL,
	STOP_DEATH
}					t_stop;

#endif