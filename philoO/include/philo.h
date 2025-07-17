/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/07/17 12:47:03 by vpoka            ###   ########.fr       */
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

t_data	*initialize_data(int argc, char **argv);

//------------------------------UTILS-------------------------------//

// output

t_error	error_msg(char *msg1, char *msg2);
void	safe_putstr_fd(char *str, int fd, pthread_mutex_t *print_mutex);
char	*get_exec_pattern(void);

// memory

void	*w_calloc(size_t nmemb, size_t size);

#endif
