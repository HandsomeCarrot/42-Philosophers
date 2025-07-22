/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:18:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/22 16:34:40 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static void	assign_forks(t_philo *philo, t_data *data)
{
	t_count	own_fork;
	t_count	neighbors_fork;

	own_fork = philo->id;
	neighbors_fork = (own_fork + 1) % data->input.philo_count;
	if (philo->id % 2 == 0)
	{
		philo->mutexes.first_fork = &data->mutexes.fork_mutexes[own_fork];
		philo->mutexes.second_fork = &data->mutexes.fork_mutexes[neighbors_fork];
	}
	else
	{
		philo->mutexes.first_fork = &data->mutexes.fork_mutexes[neighbors_fork];
		philo->mutexes.second_fork = &data->mutexes.fork_mutexes[own_fork];
	}
}

// docs
static void	assign_mutexes(t_philo *philo, t_data *data)
{
	philo->mutexes.print = &data->mutexes.print_mutex;
	philo->mutexes.term_flag = &data->mutexes.term_mutex;
	philo->mutexes.meal = &data->mutexes.meal_mutexes[philo->id];
	philo->mutexes.full = &data->mutexes.full_mutexes[philo->id];
	philo->mutexes.start = &data->mutexes.start_mutexes[philo->id];
	assign_forks(philo, data);
}

// docs
static t_error	init_philo(t_philo *philo, t_data *data)
{
	assign_mutexes(philo, data);
	return (SUCCESS);
}

// docs
static t_error	init_all_philos(t_data *data)
{
	t_count	philo_index;

	philo_index = 0;
	while (philo_index < data->input.philo_count)
	{
		data->philos.philo_data[philo_index].id = philo_index;
		if (init_philo(&data->philos.philo_data[philo_index], data) != SUCCESS)
			return (ERROR);
		philo_index++;
	}
	return (SUCCESS);
}

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
	data->philos.philo_data = w_calloc(philos, sizeof(t_philo));
	if (!data->philos.philo_data)
		return (ERROR);
	if (init_all_philos(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}