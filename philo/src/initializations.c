/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/25 16:54:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Allocates memory for an array of elements and initializes them to 0.
 *
 * @param nmemb The number of elements to allocate memory for.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	memset(res, 0, nmemb * size);
	return (res);
}

int	initialize_structs(t_program **program)
{
	if (!program)
		return (1);
	*program = (t_program *)ft_calloc(1, sizeof(t_program));
	if (!*program)
	{
		error_msg("calloc for t_program failed");
		return (1);
	}
	(*program)->config = (t_config *)ft_calloc(1, sizeof(t_config));
	if (!(*program)->config)
	{
		error_msg("calloc for t_config failed");
		return (1);
	}
	(*program)->mutexes = (t_mutex_data *)ft_calloc(1, sizeof(t_mutex_data));
	if (!(*program)->mutexes)
	{
		error_msg("calloc for t_mutex_data failed");
		return (1);
	}
	return (0);
}

int	initialize_mutexes(t_program *program)
{
	unsigned int	pos;
	int				status;
	
	if (!program)
		return (1);
	program->mutexes->forks = ft_calloc(program->config->number_of_philos + 1, \
			sizeof(pthread_mutex_t *));
	if (!program->mutexes->forks)
		return (1);
	pos = 0;
	while (pos < program->config->number_of_philos)
	{
		status = pthread_mutex_init(program->mutexes->forks[pos], NULL);
		if (status != 0)
			return (1);
		pos++;
	}
	status = pthread_mutex_init(program->mutexes->death, NULL);
	if (status != 0)
		return (1);
	return (0);
}
