/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/18 12:00:18 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "types.h"
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//------------------------------INITIALIZATION-------------------------------//

t_error	initialize_data(int argc, char **argv, t_data **data_ptr);

// input

t_error	proccess_input(bool meal_limit, char **argv, t_data *data);

//------------------------------UTILS-------------------------------//

// output

t_error	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);
char	*get_exec_pattern(void);

// memory

void	*w_calloc(size_t nmemb, size_t size);

// conversions

t_error	atoms(const char *str, t_ms *result);
t_error	atocount(const char *str, t_count *result);

#endif
