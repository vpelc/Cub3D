# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 13:30:56 by vpelc             #+#    #+#              #
#    Updated: 2025/02/06 14:20:42 by vpelc            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME                = cub3d

# Directories
INC                 = include/
SRC_DIR             = src/
OBJ_DIR             = obj/
GNL_DIR             = include/get_next_line/

# Compiler and CFlags
CC                  = cc
CFLAGS              = -Wall -Werror -Wextra -g
RM                  = rm -f

# Additional flags
INCLUDES            = -I/usr/include -Imlx_linux -O3
LIBRARIES           = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# Source files
SRCS                = main_test.c

# File paths
SRC                 = $(addprefix $(SRC_DIR), $(SRCS))
GNL_SRC             = $(addprefix $(GNL_DIR), $(GNL_SRCS))
OBJ                 = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o) $(GNL_SRCS:.c=.o))

all:                $(NAME)

obj:
	@if [ -d $(OBJ_DIR) ]; then \
		echo "\033[1;31mDirectory already created.\033[0m"; \
	else \
		mkdir -p $(OBJ_DIR); \
		echo "\033[1;36mDirectory obj/ with files .o is being created...\033[0m"; \
	fi

# Compile object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) -I$(INC) $(INCLUDES) -c $< -o $@
#	@echo "\033[1;32mFile $@ created.\033[0m";

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) -I$(INC) -I$(GNL_DIR) $(INCLUDES) -c $< -o $@
#	@echo "\033[1;32mFile $@ created.\033[0m";

$(NAME): $(OBJ) 
	@echo "\033[1;36mCompiling so_long...\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBRARIES)
	@echo "\033[1;32mDone.\033[0m"

clean:
	@echo "\033[1;35mRemoving obj/...\033[0m"
	@$(RM) -r $(OBJ_DIR) 
	@echo "\033[1;32mAll Done for clean.\033[0m"

fclean: clean
	@echo "\033[1;35mRemoving so_long...\033[0m"
	@$(RM) $(NAME)
	@echo "\033[1;32mDone.\033[0m"

re: fclean obj all

bonus: all

.PHONY: all obj clean fclean re
