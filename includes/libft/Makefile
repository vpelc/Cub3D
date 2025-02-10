NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj
INC = -I$(INC_DIR)

SRCS = \
    $(SRC_DIR)/ft_atoi.c \
    $(SRC_DIR)/ft_isalpha.c \
    $(SRC_DIR)/ft_itoa.c \
    $(SRC_DIR)/ft_lstdelone_bonus.c \
    $(SRC_DIR)/ft_lstnew_bonus.c \
    $(SRC_DIR)/ft_memcpy.c \
    $(SRC_DIR)/ft_putendl_fd.c \
    $(SRC_DIR)/ft_strchr.c \
    $(SRC_DIR)/ft_strlcat.c \
    $(SRC_DIR)/ft_strncmp.c \
    $(SRC_DIR)/ft_substr.c \
    $(SRC_DIR)/ft_bzero.c \
    $(SRC_DIR)/ft_isascii.c \
    $(SRC_DIR)/ft_lstadd_back_bonus.c \
    $(SRC_DIR)/ft_lstiter_bonus.c \
    $(SRC_DIR)/ft_lstsize_bonus.c \
    $(SRC_DIR)/ft_memmove.c \
    $(SRC_DIR)/ft_putnbr_fd.c \
    $(SRC_DIR)/ft_strdup.c \
    $(SRC_DIR)/ft_strlcpy.c \
    $(SRC_DIR)/ft_strnstr.c \
    $(SRC_DIR)/ft_tolower.c \
    $(SRC_DIR)/ft_calloc.c \
    $(SRC_DIR)/ft_isdigit.c \
    $(SRC_DIR)/ft_lstadd_front_bonus.c \
    $(SRC_DIR)/ft_lstlast_bonus.c \
    $(SRC_DIR)/ft_memchr.c \
    $(SRC_DIR)/ft_memset.c \
    $(SRC_DIR)/ft_putstr_fd.c \
    $(SRC_DIR)/ft_striteri.c \
    $(SRC_DIR)/ft_strlen.c \
    $(SRC_DIR)/ft_strrchr.c \
    $(SRC_DIR)/ft_toupper.c \
    $(SRC_DIR)/ft_isalnum.c \
    $(SRC_DIR)/ft_isprint.c \
    $(SRC_DIR)/ft_lstclear_bonus.c \
    $(SRC_DIR)/ft_lstmap_bonus.c \
    $(SRC_DIR)/ft_memcmp.c \
    $(SRC_DIR)/ft_putchar_fd.c \
    $(SRC_DIR)/ft_split.c \
    $(SRC_DIR)/ft_strjoin.c \
    $(SRC_DIR)/ft_strmapi.c \
    $(SRC_DIR)/ft_strtrim.c \
    $(SRC_DIR)/ft_printf.c \
    $(SRC_DIR)/ft_putstr.c\
    $(SRC_DIR)/ft_putnbr.c \
    $(SRC_DIR)/ft_putchar.c \
    $(SRC_DIR)/ft_putadress.c \
    $(SRC_DIR)/ft_putunsigned.c \
    $(SRC_DIR)/ft_puthex.c \
    $(SRC_DIR)/ft_strchr_printf.c \
    $(SRC_DIR)/get_next_line.c \
    $(SRC_DIR)/get_next_line_utils.c \


OBJ = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RED = \033[31m
YELLOW = \033[93m
GREEN = \033[32m
RESET = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m

ICON_COMPILE = "🔨"
ICON_CLEAN = "🧹"
ICON_FCLEAN = "🗑️"
ICON_REBUILD = "🔄"
ICON_CONFETTI = "🎉"

all: $(NAME)
	@echo "$(BOLD)$(GREEN)Library $(NAME) has been created successfully!$(RESET)"
	@echo "$(BOLD)$(GREEN)$(ICON_CONFETTI) Compilation successful! $(ICON_CONFETTI)$(RESET)"
	@echo "🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊🎉🎊"

$(NAME): $(OBJ)
	@echo "$(BOLD)$(YELLOW)🏗️  Archiving $(NAME)... $(RESET)"
	@ar rcs $@ $(OBJ)
	@echo "$(BOLD)$(GREEN)$(ICON_CONFETTI) Library $(NAME) successfully created! $(ICON_CONFETTI)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo -n "$(BOLD)$(YELLOW)🔨 Compiling $<... $(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(BOLD)$(YELLOW)🔨 Compiling $<... Done!$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD)$(RED)$(ICON_CLEAN) Cleaned up object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BOLD)$(RED)$(ICON_FCLEAN) Cleaned up all files.$(RESET)"

re: fclean all
	@echo "$(BOLD)$(YELLOW)$(ICON_REBUILD) Rebuild complete!$(RESET)"

.PHONY: all clean fc
