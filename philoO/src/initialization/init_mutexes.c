/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:28:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/20 10:45:59 by vpoka            ###   ########.fr       */
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
static pthread_mutex_t	*new_mutex_array(t_data *data)
{
	pthread_mutex_t	*mutexes;
	t_count			count;
	t_count			index;

	if (!data)
		return (error_msg("missing parameters", "new_mutex_array"));
	count = data->input.philo_count;
	mutexes = w_calloc(count, sizeof(pthread_mutex_t));
	if (!mutexes)
		return (NULL);
	index = 0;
	while (index < count)
	{
		if (init_mutex(mutexes + index) != SUCCESS)
		{
			// destroy and free mutexes
			return (NULL);
		}
		index++;
	}
	return (mutexes);
}

// docs
t_error	create_mutexes(t_data *data)
{
	if (!data)
		return (error_msg("missing parameters", "create_mutexes"));
	if (init_mutex(&data->mutexes.print_mutex) != SUCCESS)
		return (ERROR);
	if (init_mutex(&data->mutexes.term_mutex) != SUCCESS)
		return (ERROR);
	data->mutexes.start_mutexes = new_mutex_array(data);
	if (!data->mutexes.start_mutexes)
		return (ERROR);
	data->mutexes.fork_mutexes = new_mutex_array(data);
	if (!data->mutexes.fork_mutexes)
		return (ERROR);
	data->mutexes.meal_mutexes = new_mutex_array(data);
	if (!data->mutexes.meal_mutexes)
		return (ERROR);
	data->mutexes.full_mutexes = new_mutex_array(data);
	if (!data->mutexes.full_mutexes)
		return (ERROR);
}
