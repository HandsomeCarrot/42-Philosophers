# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 19:28:52 by vpoka             #+#    #+#              #
#    Updated: 2025/07/02 21:48:02 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ EXECUTABLES ================================ #

NAME			= philo
NAME_GARBAGE	= garbage
NAME_SANITIZE	= sanitize
ALL_NAMES		= $(NAME) $(NAME_GARBAGE) $(NAME_SANITIZE)

# ================================ COMPILATION ================================ #

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
GARBAGEFLAG	= -g
SANITIZEFLAGS	= $(GARBAGEFLAG) -fsanitize=thread
INCLUDES		= -Iincludes

# ================================== PATHS =================================== #

SRCS_DIR		= src/
OBJS_DIR		= obj/

# ================================== FILES =================================== #

SRCS			= $(wildcard src/*.c) \
				  $(wildcard src/thread/*.c)

OBJS			= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# ================================= UTILITIES ================================= #

RM				= rm -rf
TOTAL_SRCS		:= $(words $(SRCS))
CURRENT			:= 0

# Progress display function for compilation
define progress
$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
@printf "\rCompiling files: [$(CURRENT)/$(TOTAL_SRCS)] %s" "$(notdir $<)"
endef

# Link completion message
define link_complete
@printf "\rCompiling files: [$(TOTAL_SRCS)/$(TOTAL_SRCS)] Complete!%*s\n" 20 ""
@printf "Linking executable..."
@$(CC) -o $@ $^ $(INCLUDES) $(CFLAGS)
@printf " Done!\n"
@echo "✓ $@ built successfully"
endef

# ================================== RULES =================================== #

# Default target
all: $(NAME)

# Standard build
$(NAME): $(OBJS)
	$(call link_complete)

# Build with debugging symbols
garbage: CFLAGS += $(GARBAGEFLAG)
garbage: $(OBJS)
	$(call link_complete)

# Sanitize build with thread sanitizer for race condition detection
sanitize: CFLAGS += $(SANITIZEFLAGS)
sanitize: $(OBJS)
	$(call link_complete)

# Compile source files to object files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(call progress)
	@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

# ================================= CLEANUP ================================== #

# Remove object files
clean:
	$(RM) $(OBJS_DIR)

# Remove object files and executables
fclean: clean
	$(RM) $(ALL_NAMES)

# Rebuild everything
re: fclean all

# ================================= PHONY =================================== #

.PHONY: all debug sanitize clean fclean re
