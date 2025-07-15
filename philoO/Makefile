# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/15 10:58:10 by vpoka             #+#    #+#              #
#    Updated: 2025/07/15 13:12:29 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 19:28:52 by vpoka             #+#    #+#              #
#    Updated: 2025/07/12 17:57:48 by vpoka            ###   ########.fr        #
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
SANITIZEFLAGS = $(GARBAGEFLAG) -fsanitize=thread
INCLUDES = -Iincludes

# ================================== PATHS =================================== #

SRCS_DIR = src/
OBJS_DIR = obj/

# ================================== FILES =================================== #

SRCS =	$(shell find src -name "*.c")

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# ================================= UTILITIES ================================= #

RM = rm -rf
TOTAL_SRCS := $(words $(SRCS))

# Progress display function for compilation
define progress
	@printf "\r$(CYAN)Compiling files: %s$(RST)" "$(notdir $<)"
endef

# Link completion message
define link_complete
	@printf "\r$(GREEN)Compiling files: [$(TOTAL_SRCS)/$(TOTAL_SRCS)] Complete!%*s\n$(RST)" 20 ""
	@printf "$(YELLOW)Linking executable...$(RST)"
	@$(CC) -o $@ $^ $(INCLUDES) $(CFLAGS)
	@printf "$(GREEN) Done!\n$(RST)"
	@echo "$(GREEN)✓ $@ built successfully$(RST)"
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
	@echo -n "$(RED)deleting object files...$(RST)"
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN) Done!$(RST)"

# Remove object files and executables
fclean: clean
	@echo -n "$(RED)deleting executables...$(RST)"
	@$(RM) $(ALL_NAMES)
	@echo "$(GREEN) Done!$(RST)"

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

.PHONY: all garbage sanitize g s clean fclean c f re
