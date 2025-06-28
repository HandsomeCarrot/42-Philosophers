/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:24:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/06/28 18:56:34 by vpoka            ###   ########.fr       */
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
	return (\
		"./philo" \
		"<number_of_philosophers>" \
		"<time_to_die>" \
		"<time_to_eat>" \
		"<time_to_sleep>" \
		"[number_of_times_each_philosopher_must_eat]"\
	);
}

/**
 * @brief Prints error messages to standard error output.
 *
 * This function writes error messages to STDERR_FILENO in a standardized format.
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
	write(STDERR_FILENO, "-philo", sizeof(char) * 8);
	if (msg1)
	{
		write(STDERR_FILENO, ": ", sizeof(char) * 2);
		write (STDERR_FILENO, msg1, sizeof(char) * ft_strlen(msg1));
	}
	if (msg2)
	{
		write(STDERR_FILENO, ": ", sizeof(char) * 2);
		write (STDERR_FILENO, msg2, sizeof(char) * ft_strlen(msg2));
	}
	write(STDERR_FILENO, "\n", sizeof(char) * 1);
}

/**
 * @brief Safely writes a string to a file descriptor with mutex protection.
 *
 * This function provides thread-safe string output by acquiring a print mutex
 * before writing and releasing it afterward. It ensures atomic write operations
 * when multiple threads might be attempting to write simultaneously.
 *
 * @param str The string to write. If NULL, the function returns immediately.
 * @param fd The file descriptor to write to. Must be a valid, open descriptor.
 * @param program Pointer to the program structure containing the print mutex.
 * @return SUCCESS (0) if the string was written successfully,
 *         ERROR (1) if mutex operations fail or invalid parameters are provided.
 * @note The function handles NULL string input gracefully by returning early.
 * @warning The caller must ensure the program structure and its mutexes are
 *          properly initialized before calling this function.
 * @see t_program
 */
int	safe_putstr_fd(char *str, int fd, t_program *program)
{
	if (!str || fd < 0)
		return (ERROR);
	if (pthread_mutex_lock(&program->mutexes->print))
		return (ERROR);
	write(fd, str, sizeof(char) * ft_strlen(str));
	if (pthread_mutex_unlock(&program->mutexes->print))
		return (ERROR);
	return (SUCCESS);
}
