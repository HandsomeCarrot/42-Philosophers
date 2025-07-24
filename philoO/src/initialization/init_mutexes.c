/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:28:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 15:15:35 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static t_error	init_mutex(pthread_mutex_t *mutex)
{
	int	error;

	if (!mutex)
		return (error_msg("missing parameters", "init_mutex"));
	error = pthread_mutex_init(mutex, NULL);
	if (error == 0)
		return (SUCCESS);
	else if (error == ENOMEM)
		error_msg("failed to initialize mutex", "out of memory");
	else
		error_msg("failed to initialize mutex", NULL);
	return (ERROR);
}

// docs
static pthread_mutex_t	*new_mutex_array(t_count array_size)
{
	pthread_mutex_t	*mutexes;
	t_count			index;

	mutexes = w_calloc(array_size, sizeof(pthread_mutex_t));
	if (!mutexes)
		return (NULL);
	index = 0;
	while (index < array_size)
	{
		if (init_mutex(mutexes + index) != SUCCESS)
		{
			destroy_mutex_array(index + 1, &mutexes);
			return (NULL);
		}
		index++;
	}
	return (mutexes);
}

// docs
t_error	create_mutexes(t_data *data)
{
	t_all_mutexes	mutexes;
	t_count			philo_count;

	mutexes = data->mutexes;
	philo_count = data->input.philo_count;
	if (init_mutex(&mutexes.print_mutex) != SUCCESS)
		return (ERROR);
	if (init_mutex(&mutexes.term_mutex) != SUCCESS)
		return (ERROR);
	mutexes.start_mutexes = new_mutex_array(philo_count + 1);
	if (!mutexes.start_mutexes)
		return (ERROR);
	mutexes.fork_mutexes = new_mutex_array(philo_count);
	if (!mutexes.fork_mutexes)
		return (ERROR);
	mutexes.meal_mutexes = new_mutex_array(philo_count);
	if (!mutexes.meal_mutexes)
		return (ERROR);
	mutexes.full_mutexes = new_mutex_array(philo_count);
	if (!mutexes.full_mutexes)
		return (ERROR);
	return (SUCCESS);
}
