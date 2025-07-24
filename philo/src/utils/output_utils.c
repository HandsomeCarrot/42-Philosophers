/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/24 16:20:35 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

// docs
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

// docs
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex)
{
	if (!str || fd < 0)
		return ;
	w_mutex(LOCK, print_mutex);
	write(fd, str, sizeof(char) * ft_strlen(str));
	w_mutex(UNLOCK, print_mutex);
}

// docs
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

// docs
// use write instead of printf?
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
