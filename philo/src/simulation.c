/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:57:12 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/30 01:55:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static void	create_philo(t_ms id, t_program *program)
{
	program->philos[id].id = id;
	program->philos[id].last_meal = 0;
	program->philos[id].meals_eaten = 0;
	program->philos[id].input = &program->input;
	program->philos[id].mutexes = &program->mutexes;
	program->philos[id].global_error = &program->error;
	if (pthread_create(&program->philos[id].thread, NULL, routine_start, &program->philos[id]))
	{
		set_error(ERROR, program);
		pthread_mutex_lock(program->mutexes.print);
		error_msg("failed to create philo: ", mstoa(id));
		pthread_mutex_unlock(program->mutexes.print);	
		exit_philo(ERROR, program);
	}
}

// docs
void	start_simulation(t_program *program)
{
	t_ms	philo_count;
	t_ms	philo_index;

	if (!program)
		exit_philo(ERROR, program);
	philo_index = 0;
	philo_count = program->philo_count;
	if (get_time_in_ms(&program->input.sim_start_time, program->mutexes.print))
		exit_philo(ERROR, program);
	while (philo_index < philo_count)
	{
		create_philo(philo_index, program);
		philo_index++;
	}
}
