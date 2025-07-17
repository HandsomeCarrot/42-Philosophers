/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:23:07 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/17 12:52:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_error	initialize_data(int argc, char **argv, t_data **data_ptr)
{
	t_data	*data;

	if (!argv || !data_ptr)
		return (error_msg("missing parameters", "initialize_data"));
	data = w_calloc(1, sizeof(t_data));
	if (!data)
		return (ERROR);
	*data_ptr = data;
	if (get_input())
		return (ERROR);
}
