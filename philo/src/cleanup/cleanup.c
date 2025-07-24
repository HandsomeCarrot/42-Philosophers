/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:50:37 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 01:44:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
t_error	erase_data(t_data *data)
{
	t_error	error;

	if (!data)
		return (SUCCESS);
	error = join_all_threads(data);
	if (destroy_all_mutexes(data) != SUCCESS)
		error = ERROR;
	if (free_philo_data(data) != SUCCESS)
		error = ERROR;
	free(data);
	return (error);
}
