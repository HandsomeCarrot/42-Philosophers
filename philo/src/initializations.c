/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:58:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/03/24 17:18:31 by vpoka            ###   ########.fr       */
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

int	initialize_structs(t_params **config)
{
	*config = (t_params *)ft_calloc(1, sizeof(t_params));
	if (!*config)
	{
		error_msg("calloc for t_params failed");
		return (1);
	}
	return (0);
}
