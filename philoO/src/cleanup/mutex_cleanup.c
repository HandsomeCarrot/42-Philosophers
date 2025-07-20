/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/20 11:13:40 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static t_error	destroy_mutex(pthread_mutex_t *mutex)
{
	int	error;

	if (!mutex)
		return (error_msg("missing parameters", "destroy_mutex"));
	error = pthread_mutex_destroy(mutex);
	if (error == 0)
		return (SUCCESS);
	if (error == EBUSY)
		error_msg("failed to destroy mutex", "mutex is in use");
	else
		error_msg("failed to destroy mutex", NULL);
	return (ERROR);
}

t_error	destroy_mutex_array(t_count count, pthread_mutex_t **mutex_array)
{
	t_count	index;

	if (!mutex_array || !*mutex_array)
		return (error_msg("missing parameters", "mutex_array_cleanup"));
	index = 0;
	while (index < count)
	{
		if (destroy_mutex((*mutex_array) + index) != SUCCESS)
			return (ERROR);
		index++;
	}
	free(*mutex_array);
	return (SUCCESS);
}