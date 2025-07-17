/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:23:07 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/17 12:47:17 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_data	*initialize_data(int argc, char **argv)
{
	t_data	*data;

	if (!argv)
		return (error_msg("missing parameters", "initialize_data"));
	data = w_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
}
