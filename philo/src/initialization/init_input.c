/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:53:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 21:04:00 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
static t_error	atoms(const char *str, t_ms *result)
{
	t_ms	res;
	t_ms	prev;
	char	*nptr;

	res = 0;
	nptr = (char *)str;
	while (nptr && *nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			error_msg("Non-numeric character in argument", (char *)str);
			return (ERROR);
		}
		prev = res;
		res = res * 10 + (*nptr - '0');
		if (res < prev)
		{
			error_msg("number is too large (uint64)", (char *)str);
			return (ERROR);
		}
		nptr++;
	}
	*result = res;
	return (SUCCESS);
}

// docs
static t_error	atocount(const char *str, t_count *result)
{
	t_count	res;
	t_count	prev;
	char	*nptr;

	res = 0;
	nptr = (char *)str;
	while (nptr && *nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			error_msg("Non-numeric character in argument", (char *)str);
			return (ERROR);
		}
		prev = res;
		res = res * 10 + (*nptr - '0');
		if (res < prev)
		{
			error_msg("number is too large (uint16)", (char *)str);
			return (ERROR);
		}
		nptr++;
	}
	*result = res;
	return (SUCCESS);
}

// docs
static t_error	get_counts(bool meal_limit, char **argv, t_data *data)
{
	if (atocount((const char *)argv[1], &data->input.philo_count) != SUCCESS)
		return (ERROR);
	if (data->input.philo_count < 1)
		return (error_msg("Incorrect input", "needs at least 1 philosopher"));
	if (meal_limit)
	{
		if (atocount((const char *)argv[5], &data->input.meal_limit) != SUCCESS)
			return (ERROR);
		data->input.has_meal_limit = true;
	}
	return (SUCCESS);
}

// docs
static t_error	get_times(char **argv, t_data *data)
{
	if (atoms((const char *)argv[2], &data->input.time_to_die) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[3], &data->input.time_to_eat) != SUCCESS)
		return (ERROR);
	if (atoms((const char *)argv[4], &data->input.time_to_sleep) != SUCCESS)
		return (ERROR);
	if (data->input.philo_count % 2 == 1)
	{
		data->input.time_to_think = data->input.time_to_eat * 2;
		data->input.time_to_think -= data->input.time_to_sleep;
		data->input.time_to_think *= 0.1;
	}
	return (SUCCESS);
}

// docs
t_error	proccess_input(bool meal_limit, char **argv, t_data *data)
{
	if (!argv || !data)
		return (error_msg("missing parameters", "process_input"));
	if (get_counts(meal_limit, argv, data) != SUCCESS)
		return (ERROR);
	if (get_times(argv, data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
