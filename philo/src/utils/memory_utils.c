/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:08:46 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:32:51 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Allocates and zero-initializes memory for an array of elements.
 *
 * This function allocates memory for an array of `nmemb` elements of `size`
 * bytes each and returns a pointer to the allocated memory. The memory is
 * set to zero. If the allocation fails, an error message is printed and
 * NULL is returned.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size in bytes of each element.
 * @return void* Pointer to allocated memory, or NULL if allocation fails.
 * @note The caller is responsible for freeing the allocated memory.
 * @warning This function will exit the program if memory allocation fails.
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
