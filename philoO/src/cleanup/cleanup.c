/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 23:50:37 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/23 00:18:58 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
void	erase_data(t_data *data)
{
	if (!data)
		return ;
	// join all threads
	// destroy all mutexes
	// free philo data
	// free philo threads
	free(data);
}
