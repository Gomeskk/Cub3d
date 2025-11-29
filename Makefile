# Silence all commands unless explicitly printed
MAKEFLAGS 		+= --silent

### COLOURS ###
BOLD    		= \033[1m
GREEN   		= \033[32m
RED     		= \033[31m
YELLOW 		 	= \033[33m
CYAN    		= \033[36m
PINK    		= \e[1;35m
PURPLE  		= \e[0;95m
WHITE   		= \e[1;37m
DEFAULT 		= \e[0m

# Variables
NAME 			= cub3d
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g
INCLUDES 		= -I inc/

### CUB3D SRCS ###
SRCS 			= $(PARSER_SRCS) cub3d.c exit_error.c
SRC_DIR 		= src/

PARSER_SRCS		= parser.c
PARSER_DIR		= src/parser/
PARSER 			=  $(addprefix $(PARSER_DIR), $(PARSER_SRCS))

TOTAL_SRCS 		= $(words $(SRCS))
FILES 			= 0

### OBJECTS ###
OBJ_DIR			= obj/
OBJS 			= $(SRCS:%.c=$(OBJ_DIR)%.o)

# Library paths
LIBFT_PATH      = complete_lib/42_Libft
LIBFT           = $(LIBFT_PATH)/libft.a
FT_PRINTF_PATH  = complete_lib/42_Printf
FT_PRINTF       = $(FT_PRINTF_PATH)/libftprintf.a
GNL_PATH        = complete_lib/42_GNL
GNL             = $(GNL_PATH)/libgnl.a
PERSONAL_LIBS   = -lft -lgnl -lftprintf
LIBS			= -L$(LIBFT_PATH) -L$(FT_PRINTF_PATH) -L$(GNL_PATH) $(PERSONAL_LIBS)

### MLX COMPILE FLAGS ###
MLX_CC			= -L complete_lib/minilibx-linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
MLX_INC			= -I/usr/include -Imlx_linux -O3 




vpath %.c $(SRC_DIR) $(PARSER_DIR)

all: $(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
				@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && \
    			$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
    			$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(PINK),$(WHITE)Compiling$(DEFAULT) $@)

$(OBJ_DIR):
				@mkdir -p $@

# Add mlx library as dependency here
$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF) $(GNL) $(OBJ_DIR)
				@echo "$(WHITE)Bringing $(PINK)$(NAME)$(WHITE) to life!$(DEFAULT)"
				@echo "$(WHITE)Creating $(PINK)$(NAME)'s$(WHITE) executable...$(DEFAULT)"
				@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX_CC) $(LIBS) -o $@
				@echo "$(PINK)$(NAME) was born!$(DEFAULT)"

$(LIBFT):
				@make -C $(LIBFT_PATH)

$(FT_PRINTF):
				@make -C $(FT_PRINTF_PATH)

$(GNL):
				@make -C $(GNL_PATH)

clean:
				@echo "$(PINK)Cleaning object files...$(DEFAULT)"
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
				@echo "$(PINK)Cleaning executable...$(DEFAULT)"
				@make fclean -C $(LIBFT_PATH)
				@make fclean -C $(FT_PRINTF_PATH)
				@make fclean -C $(GNL_PATH)
				@rm -f $(NAME)
				@echo "$(WHITE)⋆˚࿔ Executable Killed˚⋆♡$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

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
