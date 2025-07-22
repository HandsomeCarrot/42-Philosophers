/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:50:37 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 01:20:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
void	erase_data(t_data *data)
{
	t_error	error;

	if (!data)
		return ;
	error = join_all_threads(data);
	// if (destroy all mutexes)
	// 	error = ERROR;
	// if (free philo data)
	// 	error = ERROR;
	free(data);
}
