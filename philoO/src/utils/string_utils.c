/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:05:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/18 12:08:33 by vpoka            ###   ########.fr       */
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
