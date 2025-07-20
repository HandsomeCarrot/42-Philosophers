/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:28:32 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/20 10:36:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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
	mutexes = w_calloc(count, sizeof(pthread_mutex_t));
	if (!mutexes)
		return (NULL);
	index = 0;
	count = data->input.philo_count;
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
}