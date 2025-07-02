# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 19:28:52 by vpoka             #+#    #+#              #
#    Updated: 2025/07/02 18:58:01 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

DEBUGFLAGS = -g
SANFLAGS = $(DEBUGFLAGS) -fsanitize=thread

INCLUDES = -Iincludes

RM = rm -rf

SRCS_DIR = src/
SRCS =	$(wildcard src/*.c) \
		$(wildcard src/thread/*.c)

OBJS_DIR = obj/
OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

ifeq ($(DEBUG), 1)
CFLAGS += $(DEBUGFLAGS)
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES)

debug: CFLAGS += $(DEBUGFLAGS)
debug: $(NAME)

sanitize: CFLAGS += $(SANFLAGS)
sanitize: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all debug sanitize clean fclean re
