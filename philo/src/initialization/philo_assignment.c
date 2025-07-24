/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_assignment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:45:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/01/04 16:45:00 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	assign_forks(t_philo *philo, t_data *data)
{
	t_count	own_fork;
	t_count	next_fork;

	own_fork = philo->id;
	next_fork = (own_fork + 1) % data->input.philo_count;
	if (philo->id % 2 == 0)
	{
		philo->mutexes.first_fork = &data->mutexes.fork_mutexes[own_fork];
		philo->mutexes.second_fork = &data->mutexes.fork_mutexes[next_fork];
	}
	else
	{
		philo->mutexes.first_fork = &data->mutexes.fork_mutexes[next_fork];
		philo->mutexes.second_fork = &data->mutexes.fork_mutexes[own_fork];
	}
}

void	assign_mutexes(t_philo *philo, t_data *data)
{
	philo->mutexes.print = &data->mutexes.print_mutex;
	philo->mutexes.term_flag = &data->mutexes.term_mutex;
	philo->mutexes.meal = &data->mutexes.meal_mutexes[philo->id];
	philo->mutexes.full = &data->mutexes.full_mutexes[philo->id];
	philo->mutexes.start = &data->mutexes.start_mutexes[philo->id];
	assign_forks(philo, data);
}

t_ms	calculate_initial_think_time(t_count id)
{
	if (id == 0)
		return (0);
	return (id % 2);
}
