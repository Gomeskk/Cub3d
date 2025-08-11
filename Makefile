# Silence all commands unless explicitly printed
MAKEFLAGS += --silent

### COLOURS ###
RESET   = \033[0m
BOLD    = \033[1m
GREEN   = \033[32m
RED     = \033[31m
YELLOW  = \033[33m
CYAN    = \033[36m
MAGENTA = \033[35m
PINK    = \e[1;35m
PURPLE  = \e[0;95m
WHITE   = \e[1;37m
DEFAULT = \e[0m

# Variables
MLX_DIR = complete_lib/minilibx-linux
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = inc/
IFLAGS = -I $(INCLUDES) -I $(MLX_DIR)

# Library paths
LIBFT_PATH      = complete_lib/42_Libft
LIBFT           = $(LIBFT_PATH)libft.a
FT_PRINTF_PATH  = complete_lib/42_Printf
FT_PRINTF       = $(FT_PRINTF_PATH)libftprintf.a
GNL_PATH        = complete_lib/42_GNL
GNL             = $(GNL_PATH)libgnl.a
PERSONAL_LIBS   = -lft -lgnl -lftprintf

SRC_DIR = src/
OBJ_DIR = objs/
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

NAME = cub3d
TOTAL_SRCS = $(words $(SRCS))
FILES = 0

# Combined library flags
LIBS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz -L$(LIBFT_PATH) -L$(FT_PRINTF_PATH) -L$(GNL_PATH) $(PERSONAL_LIBS)

# Ensure mlx lib is built before building our project
all: mlx $(NAME)

# Build mlx library if missing
$(MLX_DIR)/libmlx_Linux.a:
	@make -C $(MLX_DIR) # > /dev/null 2>&1

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ && \
    $(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
    $(call PRINT_PROGRESS,$(TOTAL_SRCS),$(PINK),$(WHITE)Compiling$(DEFAULT) $@)

$(OBJ_DIR):
	@mkdir -p $@

# Add mlx library as dependency here
$(NAME): $(MLX_DIR)/libmlx_Linux.a $(LIBFT) $(FT_PRINTF) $(GNL) $(OBJS)
	@echo "$(WHITE)Bringing $(PINK)$(NAME)$(WHITE) to life!$(DEFAULT)"
	@echo "$(WHITE)Creating $(PINK)$(NAME)'s$(WHITE) executable...$(DEFAULT)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(PINK)$(NAME) was born!$(DEFAULT)"

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_PATH)

$(GNL):
	@make -C $(GNL_PATH)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C $(MLX_DIR) # > /dev/null 2>&1
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(FT_PRINTF_PATH)
	@make clean -C $(GNL_PATH)
	@rm -rf $(OBJ_DIR)
	@echo "$(WHITE)✩°｡⋆ $(PINK)Files Cleaned$(WHITE) ⋆｡°✩ \n \
    (\ (\    \n \
    ( ~_•)    \n \
    (っ▄︻▇〓▄︻┻┳═ ─ ҉.  \n \
     /　 )  / \    \n \
    (/￣∪  /   \ $(DEFAULT)"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@make clean -C $(MLX_DIR) # > /dev/null 2>&1
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(FT_PRINTF_PATH)
	@make fclean -C $(GNL_PATH)
	@rm -f $(NAME)
	@echo "$(WHITE)⋆˚࿔ Executable Killed˚⋆♡$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re mlx

define PRINT_PROGRESS
	if [ "$(FILES)" -eq "1" ]; then \
		printf "\033[0K$(3)\n["; \
	else \
		printf "\033[0K\033[1F\033[0K$(3)\n["; \
	fi; \
	for i in `seq 1 $$(expr $(FILES) \* 70 / $(1))`; do \
		printf "$(2)=\033[0m"; \
	done; \
	for i in `seq 1 $$(expr 70 - $(FILES) \* 70 / $(1))`; do \
		printf " "; \
	done; \
	printf "] $$(expr $(FILES) \* 100 / $(1))%%"; \
	if [ "$(FILES)" -eq "$(1)" ]; then \
		printf "\n"; \
	fi
endef
