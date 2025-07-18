/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:16:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/18 12:15:17 by vpoka            ###   ########.fr       */
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
//static char	*get_state_message(t_philo_state state)
//{
//	if (state == FORK)
//		return ("has taken a fork");
//	else if (state == EATING)
//		return ("is eating");
//	else if (state == SLEEPING)
//		return ("is sleeping");
//	else if (state == THINKING)
//		return ("is thinking");
//	else if (state == DEATH)
//		return ("died");
//	return (NULL);
//}

// docs
//t_error	print_philo_state(t_philo_state state, t_ms *timestamp, 
// t_philo *philo)
//{
//	char	*state_message;
//	t_ms	elapsed_time;

//	if (!philo)
//	{
//		error_msg("missing parameters", "print_philo_state");
//		return (ERROR);
//	}
//	state_message = get_state_message(state);
//	if (!state_message)
//		return (ERROR);
//	if (w_mutex(LOCK, philo->mutexes.print))
//		return (ERROR);
//	if (get_elapsed_time_ms(&elapsed_time, philo->input))
//	{
//		w_mutex(UNLOCK, philo->mutexes.print);
//		return (ERROR);
//	}
//	printf("%lu %lu %s\n", elapsed_time, philo->id + 1, state_message);
//	if (w_mutex(UNLOCK, philo->mutexes.print))
//		return (ERROR);
//	if (timestamp)
//		*timestamp = elapsed_time;
//	return (SUCCESS);
//}

// docs
char	*get_exec_pattern(void)
{
	return ("./philo "
		"<number_of_philosophers> "
		"<time_to_die> "
		"<time_to_eat> "
		"<time_to_sleep> "
		"[number_of_times_each_philosopher_must_eat]");
}
