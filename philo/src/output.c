/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:24:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/01 17:29:40 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Returns the expected command-line usage pattern for the program.
 * 
 * This function provides the standard usage pattern that should be displayed
 * when the program is run with invalid or missing arguments.
 *
 * @return char* The usage pattern string in the format:
 *               "./philo <number_of_philosophers> <time_to_die> <time_to_eat> 
 *               <time_to_sleep> [number_of_times_each_philosopher_must_eat]"
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
 * Formats and prints error messages in two parts. If both msg1 and msg2 are
 * provided, they are concatenated with a colon separator. The output is
 * prefixed with "-philo: " for consistent error messaging.
 *
 * @param msg1 Primary error message (mandatory)
 * @param msg2 Secondary error message or context (optional)
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
 * @brief Thread-safe string output using mutex protection.
 *
 * Safely writes a string to the specified file descriptor while holding
 * a mutex lock to prevent interleaved output from multiple threads.
 * If either str is NULL or fd is invalid, the function returns immediately.
 *
 * @param str String to output
 * @param fd File descriptor to write to
 * @param print_mutex Mutex used for output synchronization
 */
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex)
{
	if (!str || fd < 0)
		return ;
	w_mutex(LOCK, print_mutex);
	write(fd, str, sizeof(char) * ft_strlen(str));
	w_mutex(UNLOCK, print_mutex);
}
