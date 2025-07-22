/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:36:31 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 01:41:04 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
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