#############################################
# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m
Magenta = \033[0;35m
CYAN = \033[0;36m
GRAY = \033[0;90m
RED = \033[0;31m
SPINNERS = "🔄 🔁 ↩️ ↪️ 🔄 🔁"

#############################################

NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm


# Source directories
SRC_DIR = src
OBJ_DIR = .cache
INCLUDES_DIR = includes

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Librairies
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./includes/minilibx
MLX = $(MLX_DIR)/libmlx.a
#############################################

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[38;5;33m ██████╗ ██╗   ██╗██████╗ ███████╗██████╗ ██████╗  \033[0m"
	@echo "\033[38;5;37m██╔════╝ ██║   ██║██╔══██╗██╔════╝╚════██╗██╔══██╗ \033[0m"
	@echo "\033[38;5;39m██║      ██║   ██║██████╔╝█████╗   █████╔╝██║  ██║ \033[0m"
	@echo "\033[38;5;45m██║      ██║   ██║██╔══██╗██╔══╝   ╚═══██╗██║  ██║ \033[0m"
	@echo "\033[38;5;51m╚██████╗ ╚██████╔╝██████╔╝███████╗██████╔╝██████╔╝ \033[0m"
	@echo "\033[38;5;57m ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝╚═════╝ ╚═════╝  \033[0m"
	@echo "                                                                       "
	@echo "$(GREEN)Building the Cube3D project...$(NC)"
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) || { echo "$(RED)Erreur: MiniLibX introuvable ou non compilée!$(NC)"; exit 1; }
	@total=$(words $(OBJ)); \
	count=0; \
	for file in $(OBJ); do \
		count=$$((count + 1)); \
		percentage=$$((count * 100 / total)); \
		progress=$$((percentage / 2)); \
		spinner=$$(echo $(SPINNERS) | cut -d ' ' -f $$(($$count % 6 + 1))); \
		bar=""; \
		for i in $$(seq 1 $$progress); do bar="$${bar}█"; done; \
		for i in $$(seq $$progress 49); do bar="$${bar}░"; done; \
		if [ $$percentage -eq 100 ]; then \
			bar="███████████████████████████████████████████████████"; \
		fi; \
		printf "\r$(YELLOW)Compiling : $${bar} %d%% $${spinner}" $$percentage; \
		sleep 0.01; \
	done; \
	printf "\n"; \
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS)
	@echo "$(GREEN)Compilation successful!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft -I$(MLX_DIR) 
	@echo "$(GREEN)Compilation successful!$(NC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning project...$(Magenta)"
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Clean successful!$(NC)"

fclean: clean
	@echo "$(YELLOW)Full clean of project...$(Magenta)"
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -f $(NAME) *.o
	@echo "$(GREEN)Fclean successful!$(NC)"

re : fclean all
	@echo "$(GREEN)Cleaned & rebuilt$(NC)"

.PHONY: all fclean clean re libft minilibx
