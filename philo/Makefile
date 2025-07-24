# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/15 10:58:10 by vpoka             #+#    #+#              #
#    Updated: 2025/07/25 00:02:33 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ EXECUTABLES ================================ #

NAME = philo
NAME_GARBAGE = garbage
NAME_SANITIZE = sanitize
ALL_NAMES = $(NAME) $(NAME_GARBAGE) $(NAME_SANITIZE)

# ================================ COMPILATION ================================ #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
GARBAGEFLAG = -g
SANITIZEFLAGS = -g -fsanitize=thread
INCLUDES = -Iinclude

# ================================== PATHS =================================== #

SRCS_DIR = src/
OBJS_DIR = obj/

# ================================== FILES =================================== #

SRCS =	$(shell find src -name "*.c")

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# ================================= UTILITIES ================================= #

RM = rm -rf

# Progress display function for compilation
define progress
	@printf "\rCompiling file: %s\n" "$(notdir $<)"
endef

# Link completion message
define link_complete
	@printf "$(YELLOW)Linking executable...$(RST)\n"
	@$(CC) -o $@ $^ $(INCLUDES) $(CFLAGS)
	@echo "$(GREEN)$@ built successfully!$(RST)"
endef
# ================================= COLORS ================================= #

RST = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
CYAN = \033[1;36m

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
	@echo "$(RED)deleting object files...$(RST)"
	@$(RM) $(OBJS_DIR)

# Remove object files and executables
fclean: clean
	@echo "$(RED)deleting executables...$(RST)"
	@$(RM) $(ALL_NAMES)

# Rebuild everything
re:
	@echo "$(YELLOW)Recompiling...$(RST)"
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

# ================================= ALIASES ================================== #

g: garbage
s: sanitize
c: clean
f: fclean

# ================================= PHONY =================================== #

.PHONY: all garbage sanitize clean fclean re g s c f
