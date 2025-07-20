/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:18:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/20 11:28:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
t_error	create_philo_data(t_data *data)
{
	t_count	philos;

	philos = data->input.philo_count;
	data->philos.last_meals = w_calloc(philos, sizeof(t_ms));
	if (!data->philos.last_meals)
		return (ERROR);
	data->philos.philo_full = w_calloc(philos, sizeof(bool));
	if (!data->philos.philo_full)
		return (ERROR);
	// create philo structs
}