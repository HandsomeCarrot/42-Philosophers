/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:08:46 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/08 16:08:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Allocates zero-initialized memory with error handling.
 *
 * Allocates memory for an array of nmemb elements of size bytes each,
 * initializing all bytes to zero. Returns NULL on allocation failure.
 *
 * @param nmemb Number of elements.
 * @param size Size in bytes of each element.
 *
 * @return Pointer to the allocated memory, or NULL on failure.
 */
void	*w_calloc(size_t nmemb, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(nmemb * size);
	if (!new_ptr)
	{
		error_msg("memory allocation failed", NULL);
		return (NULL);
	}
	memset(new_ptr, 0, nmemb * size);
	return (new_ptr);
}
