/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:53:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 17:40:43 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// docs
// TODO
void	*routine_start(void *data)
{
	t_philo	*philo;

	philo = data;
	w_mutex(LOCK, philo->mutexes->print);
	printf("started philo number: %lu\n", philo->id);
	w_mutex(UNLOCK, philo->mutexes->print);
	return (NULL);
}
