# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 19:28:52 by vpoka             #+#    #+#              #
#    Updated: 2025/07/01 17:48:46 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g

RM = rm -rf

SRCS_DIR = src/
SRCS =	$(wildcard src/*.c) \
		$(wildcard src/thread/*.c)

OBJS_DIR = obj/
OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
