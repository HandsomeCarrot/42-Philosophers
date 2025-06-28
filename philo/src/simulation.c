/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:57:12 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/28 21:37:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
static pthread_t	create_philo(t_ms id, t_program *program)
{
	t_philo		data;
	pthread_t	philo;

	data.id = id;
	data.last_meal = 0;
	data.meals_eaten = 0;
	data.mutexes = program->mutexes;
	if (pthread_create(&philo, NULL, &routine_start, &data))
	{
		set_error(ERROR, program);
		safe_putstr_fd("failed to create philo ", STDERR_FILENO, program);
		safe_putstr_fd(mstoa(id), STDERR_FILENO, program);
		safe_putstr_fd("\n", STDERR_FILENO, program);
		exit_philo(ERROR, program);
	}
	return (philo);
}

// docs
void	start_simulation(t_program *program)
{
	t_ms	nbr_of_philos;
	t_ms	philo_index;

	if (!program)
	{
		error_msg("missing program struct pointer", NULL);
		exit_philo(ERROR, program);
	}
	philo_index = 0;
	nbr_of_philos = get(NBR_OF_PHILOS);
	set_simulation_start(program);
	while (philo_index < nbr_of_philos)
	{
		program->philos[philo_index] = create_philo(philo_index, program);
		philo_index++;
	}
}
