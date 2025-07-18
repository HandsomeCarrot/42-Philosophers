/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:05:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/18 12:07:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
//static int	count_nums(t_ms number)
//{
//	int	digit_count;

//	digit_count = 0;
//	if (number == 0)
//		return (1);
//	while (number > 0)
//	{
//		number /= 10;
//		digit_count++;
//	}
//	return (digit_count);
//}

// docs
//char	*ms_to_str(t_ms number)
//{
//	char	*digit_str;
//	int		digit_count;

//	digit_count = count_nums(number);
//	digit_str = malloc((digit_count + 1) * sizeof(char));
//	if (!digit_str)
//		return (NULL);
//	digit_str[digit_count] = 0;
//	if (number == 0)
//	{
//		digit_str[0] = '0';
//		return (digit_str);
//	}
//	while (number > 0)
//	{
//		digit_count--;
//		digit_str[digit_count] = (number % 10) + '0';
//		number /= 10;
//	}
//	return (digit_str);
//}

// docs
t_error	atoms(const char *str, t_ms *result)
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
t_error	atocount(const char *str, t_count *result)
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
//int	ft_strlen(char *str)
//{
//	int	counter;

//	counter = 0;
//	while (str && *str)
//	{
//		counter++;
//		str++;
//	}
//	return (counter);
//}
