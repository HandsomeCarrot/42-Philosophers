/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 18:52:23 by vpoka            ###   ########.fr       */
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
