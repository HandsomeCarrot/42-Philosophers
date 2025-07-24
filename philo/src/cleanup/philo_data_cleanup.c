/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:36:31 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 16:18:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Free all philosopher data arrays and set pointers to NULL
 * @param data Main data structure containing philosopher arrays
 * @return SUCCESS on success, ERROR on failure
 */
t_error	free_philo_data(t_data *data)
{
	if (data->philos.last_meals)
		free(data->philos.last_meals);
	if (data->philos.philo_full)
		free(data->philos.philo_full);
	if (data->philos.philo_data)
		free(data->philos.philo_data);
	return (SUCCESS);
}
