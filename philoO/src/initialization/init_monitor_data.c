/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:00:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/22 17:21:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
void	assign_monitor_data(t_data *data)
{
	data->monitor.input = &data->input;
	data->monitor.philos.meal_mutexes = data->mutexes.meal_mutexes;
	data->monitor.philos.last_meals = data->philos.last_meals;
	data->monitor.philos.full_mutexes = data->mutexes.full_mutexes;
	data->monitor.philos.philo_full = data->philos.philo_full;
	data->monitor.term_mutex = &data->mutexes.term_mutex;
	data->monitor.term_flag = &data->term_flag;
	data->monitor.print_mutex = &data->mutexes.print_mutex;
	data->monitor.start_mutex = &data->mutexes.start_mutexes[data->input.philo_count];
}