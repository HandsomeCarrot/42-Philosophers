/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:24:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 15:36:33 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Returns the executable usage pattern string.
 *
 * This function provides a formatted string showing the correct command-line
 * usage pattern for the philo program. The string includes all required
 * parameters and the optional parameter in square brackets.
 *
 * @return A constant string containing the usage pattern. The string format is:
 *         "./philo <number_of_philosophers> <time_to_die> <time_to_eat>
 *         <time_to_sleep> [number_of_times_each_philosopher_must_eat]"
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
 * @brief Prints error messages to standard error output.
 *

 * This function writes error messages toSTDERR_FILENO in a standardized format.
 * It can handle one or two error message components, formatting them with
 * appropriate separators and a final newline.
 *
 * @param msg1 The primary error message. Can be NULL if only msg2 is provided.
 * @param msg2 The secondary error message. Can be NULL if only msg1 is provided.
 * @note If both msg1 and msg2 are NULL simultaneously,
 *       results in output being "-philo\n".
 * @warning The function assumes msg1 and msg2 are null-terminated strings if
 *          they are not NULL. Passing non-null-terminated strings may lead to
 *          undefined behavior.
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

// docs
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex)
{
	if (!str || fd < 0)
		return ;
	w_mutex(LOCK, print_mutex);
	write(fd, str, sizeof(char) * ft_strlen(str));
	w_mutex(UNLOCK, print_mutex);
}
