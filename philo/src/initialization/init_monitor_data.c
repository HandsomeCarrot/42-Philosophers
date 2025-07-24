/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:00:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 15:56:04 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
void	assign_monitor_data(t_data *data)
{
	t_monitor		*monitor;
	t_all_mutexes	*mutexes;

	monitor = &data->monitor;
	mutexes = &data->mutexes;
	monitor->input = &data->input;
	monitor->philos.meal_mutexes = mutexes->meal_mutexes;
	monitor->philos.last_meals = data->philos.last_meals;
	monitor->philos.full_mutexes = mutexes->full_mutexes;
	monitor->philos.philo_full = data->philos.philo_full;
	monitor->philos.philo_data = data->philos.philo_data;
	monitor->term_mutex = &mutexes->term_mutex;
	monitor->term_flag = &data->term_flag;
	monitor->print_mutex = &mutexes->print_mutex;
	monitor->start_mutex = &mutexes->start_mutexes[data->input.philo_count];
}
