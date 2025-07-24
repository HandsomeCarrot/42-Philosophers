/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/25 01:09:08 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/**
 * @brief Outputs an error message to stderr.
 *
 * Formats and writes an error message to standard error output. The message
 * includes the program name followed by optional error messages.
 *
 * @param msg1 First part of the error message (can be NULL).
 * @param msg2 Second part of the error message (can be NULL).
 * @return ERROR always returns this error code.
 */
t_error	error_msg(char *msg1, char *msg2)
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
	return (ERROR);
}

/**
 * @brief Safely writes a string to a file descriptor with mutex protection.
 *
 * This function ensures thread-safe writing to a file descriptor by using
 * a mutex lock during the write operation.
 *
 * @param str The string to write (ignored if NULL).
 * @param fd The file descriptor to write to (ignored if invalid).
 * @param print_mutex Mutex used to protect the write operation.
 */
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex)
{
	if (!str || fd < 0)
		return ;
	w_mutex(LOCK, print_mutex);
	write(fd, str, sizeof(char) * ft_strlen(str));
	w_mutex(UNLOCK, print_mutex);
}

/**
 * @brief Gets the string representation of a philosopher state.
 *
 * Converts a philosopher state enum value to its corresponding string
 * representation.
 *
 * @param state The philosopher state to convert.
 * @return const char* String representation of the state, or NULL if invalid.
 */
static char	*get_state_message(t_philo_state state)
{
	if (state == FORK)
		return ("has taken a fork");
	else if (state == EATING)
		return ("is eating");
	else if (state == SLEEPING)
		return ("is sleeping");
	else if (state == THINKING)
		return ("is thinking");
	else if (state == DEATH)
		return ("died");
	return (NULL);
}

/**
 * @brief Prints the current state of a philosopher with thread safety.
 *
 * Outputs the philosopher's state with timestamp and ID in a thread-safe manner.
 * Checks for termination requests before printing.
 *
 * @param state The philosopher's current state to print.
 * @param timestamp Pointer to store the timestamp when state was printed.
 * @param data Philosopher data structure containing mutexes and state.
 * @return t_error SUCCESS on success, ERROR on failure, TERMINATE if requested.
 * @note This function handles all mutex locking/unlocking internally.
 * @warning The print_mutex must be properly initialized before calling.
 */
t_error	print_state(t_philo_state state, t_ms *timestamp, t_philo *data)
{
	char	*state_message;
	t_ms	elapsed_time;
	t_error	error;

	error = SUCCESS;
	state_message = get_state_message(state);
	if (!state_message)
		error = ERROR;
	if (!error && w_mutex(LOCK, data->mutexes.print))
		error = ERROR;
	if (!error && termination_requested(data->term_flag,
			data->mutexes.term_flag))
		error = TERMINATE;
	if (!error && get_elapsed_time(&elapsed_time, data->input->sim_start_time))
		error = ERROR;
	if (!error)
		printf("%lu %d %s\n", elapsed_time, data->id + 1, state_message);
	if (w_mutex(UNLOCK, data->mutexes.print) && !error)
		error = ERROR;
	if (timestamp && !error)
		*timestamp = elapsed_time;
	return (error);
}
