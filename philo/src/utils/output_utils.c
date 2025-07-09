/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/09 17:51:04 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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

/**
 * @brief Returns a human-readable message for a philosopher's state.
 *
 * Maps an enumerated philosopher state to a descriptive string such as
 * "has taken a fork", "is eating", "is sleeping", "is thinking", or "died".
 *
 * @param state The current state of the philosopher
 * (FORK, EATING, SLEEPING, THINKING, DEATH).
 *
 * @return Pointer to a constant string describing the state,
 * or NULL if the state is invalid.
 *
 * @note The returned string must not be modified or freed by the caller.
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
 * @brief Prints the current state of a philosopher with timestamp.
 *
 * Outputs a formatted message displaying the timestamp, philosopher ID,
 * and a human-readable state such as "is eating" or "died". Ensures
 * thread-safe output by acquiring the print mutex before printing.
 *
 * @param state The current state of the philosopher (e.g., EATING, DEATH).
 * @param timestamp The time in milliseconds to display in the output.
 * @param philo Pointer to the philosopher structure whose
 * state is being printed.
 *
 * @return SUCCESS on successful output, ERROR on failure.
 *
 * @note Returns ERROR if philo is NULL, the state is invalid,
 * or mutex operations fail.
 * @warning The function must only be called with
 * a valid philosopher structure and initialized mutexes.
 */
t_error	print_philo_state(t_philo_state state, t_ms timestamp, t_philo *philo)
{
	char	*state_message;

	if (!philo)
	{
		error_msg("missing parameters", "print_philo_state");
		return (ERROR);
	}
	state_message = get_state_message(state);
	if (!state_message)
		return (ERROR);
	if (w_mutex(LOCK, philo->mutexes->print))
		return (ERROR);
	printf("%llu %llu %s\n", timestamp, philo->id + 1, state_message);
	if (w_mutex(UNLOCK, philo->mutexes->print))
		return (ERROR);
	return (SUCCESS);
}

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
