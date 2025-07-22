/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:50:37 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 01:42:33 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
t_error	erase_data(t_data *data)
{
	t_error	error;

	if (!data)
		return ;
	error = join_all_threads(data);
	if (destroy_all_mutexes(data) != SUCCESS)
		error = ERROR;
	if (free_philo_data(data) != SUCCESS)
		error = ERROR;
	free(data);
}
