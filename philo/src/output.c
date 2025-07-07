/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:24:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/07 20:57:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Returns the expected command-line usage pattern for the program.
 *
 * Provides the standard usage pattern for display when the program is run
 * with invalid or missing arguments.
 *
 * @return Pointer to a string describing the usage pattern.
 */
char	*get_exec_pattern(void)
{
	return ("./philo "
		"<number_of_philosophers> "
		"<time_to_die> "
		"<time_to_eat> "
		"<time_to_sleep> "
		"[number_of_times_each_philosopher_must_eat]");
}

/**
 * @brief Prints an error message to standard error output.
 *
 * Formats and prints error messages. If both msg1 and msg2 are provided,
 * they are concatenated with a colon separator. The output is prefixed
 * with "-philo: ".
 *
 * @param msg1 Primary error message (mandatory).
 * @param msg2 Secondary error message or context (optional).
 */
void	error_msg(char *msg1, char *msg2)
{
	write(STDERR_FILENO, "-philo", sizeof(char) * 7);
	if (msg1)
	{
		write(STDERR_FILENO, ": ", sizeof(char) * 2);
		write(STDERR_FILENO, msg1, sizeof(char) * ft_strlen(msg1));
	}
	if (msg2)
	{
		write(STDERR_FILENO, ": ", sizeof(char) * 2);
		write(STDERR_FILENO, msg2, sizeof(char) * ft_strlen(msg2));
	}
	write(STDERR_FILENO, "\n", sizeof(char) * 1);
}

/**
 * @brief Prints an error message to standard error output.
 *
 * Formats and prints error messages. If both msg1 and msg2 are provided,
 * they are concatenated with a colon separator. The output is prefixed
 * with "-philo: ".
 *
 * @param msg1 Primary error message (mandatory).
 * @param msg2 Secondary error message or context (optional).
 */
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex)
{
	if (!str || fd < 0)
		return ;
	w_mutex(LOCK, print_mutex);
	write(fd, str, sizeof(char) * ft_strlen(str));
	w_mutex(UNLOCK, print_mutex);
}
