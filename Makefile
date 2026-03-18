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
CFLAGS 			= -Wall -Wextra -Werror -g -O3
INCLUDES 		= -I inc/

RAYC_SRCS		= draw.c raycast.c dda.c
RAYC_DIR		= src/raycaster/
RAYC 			=  $(addprefix $(RAYC_DIR), $(RAYC_SRCS))

PLAYER_SRCS		= movement.c player_utils.c mouse_rotate.c keyboard_rotate.c calc_moves.c collision.c keys.c jump_crouch.c
PLAYER_DIR		= src/player/
PLAYER 			=  $(addprefix $(PLAYER_DIR), $(PLAYER_SRCS))

FEATURES_SRCS	= door.c button.c minimap.c enemy.c enemy_render.c flashlight.c enemy_move.c enemy_init.c hue_shift.c enemy_sort.c enemy_projection.c hands.c
FEATURES_DIR	= src/features/
FEATURES 		=  $(addprefix $(FEATURES_DIR), $(FEATURES_SRCS))

TEXTURES_SRCS	= texture.c texture_helper.c
TEXTURES_DIR	= src/textures/
TEXTURES		=  $(addprefix $(TEXTURES_DIR), $(TEXTURES_SRCS))

MENU_SRCS		= menu_images.c menu_images_options.c menu_images_arrays.c menu_input.c menu_input_loop.c menu_navigation.c menu_navigation_options.c menu_options_settings.c menu_render.c menu_render_utils.c menu_resolution.c menu_resolution_init.c menu_state.c menu_transparency.c menu_utils.c
MENU_DIR		= src/menu_ui/
MENU 			=  $(addprefix $(MENU_DIR), $(MENU_SRCS))

### CUB3D SRCS ###
SRCS 			= $(PARSER_SRCS) $(RAYC_SRCS) $(PLAYER_SRCS) $(FEATURES_SRCS) $(TEXTURES_SRCS) $(MENU_SRCS) cub3d.c exit_error.c init.c init_helpers.c test.c utils.c game_start.c

SRC_DIR 		= src/

PARSER_SRCS		= parser.c checker.c map_utils.c parse_map.c 
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
MLX_CC			= -L complete_lib/minilibx-linux -L/usr/lib -lmlx_Linux -lXext -lX11 -lm -lz
MLX_INC			= -I/usr/include -I mlx_linux -O3 


vpath %.c $(SRC_DIR) $(PARSER_DIR) $(RAYC_DIR) $(PLAYER_DIR) $(FEATURES_DIR) $(TEXTURES_DIR) $(MENU_DIR)

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
				@echo "$(WHITE)__$(PINK)88888888888888888888888888888888\n\
_$(PINK)88$(WHITE)_________________________________________$(PINK)88\n\
88$(WHITE)_____$(PINK)8888$(WHITE)_______________________________$(PINK)88\n\
88$(WHITE)____$(PINK)88888$(WHITE)________________________________$(PINK)88\n\
88$(WHITE)____$(PINK)88$(WHITE)__$(PINK)88$(WHITE)_______________________________$(PINK)88\n\
88$(WHITE)___$(PINK)88$(WHITE)___$(PINK)88$(WHITE)_______________________________$(PINK)88\n\
88$(WHITE)__$(PINK)888$(WHITE)___$(PINK)8888$(WHITE)____________________________$(PINK)88\n\
88$(WHITE)___$(PINK)88888888$(WHITE)_____________________________$(PINK)88\n\
88$(WHITE)__$(PINK)88$(WHITE)______$(PINK)88$(WHITE)_____________________________$(PINK)88\n\
88$(WHITE)_________________$(PINK)888$(WHITE)______________________$(PINK)88\n\
88$(WHITE)________________$(PINK)88888$(WHITE)____________________$(PINK)88\n\
88$(WHITE)______________$(PINK)888888888$(WHITE)_________________$(PINK)88\n\
88$(WHITE)_____________$(PINK)88888888888$(WHITE)________________$(PINK)88\n\
88$(WHITE)____________$(PINK)8888888888888$(WHITE)______________$(PINK)88\n\
88$(WHITE)___________$(PINK)888888888888888$(WHITE)____________$(PINK)88\n\
88$(WHITE)_________$(PINK)8888888888888888888$(WHITE)_________$(PINK)88\n\
88$(WHITE)_________$(PINK)8888888888888888888$(WHITE)_________$(PINK)88\n\
88$(WHITE)__________$(PINK)88888888888888888$(WHITE)__________$(PINK)88\n\
88$(WHITE)_________________$(PINK)8888$(WHITE)____________________$(PINK)88\n\
88$(WHITE)_______________$(PINK)8888888$(WHITE)__________________$(PINK)88\n\
88$(WHITE)____________________________$(PINK)88$(WHITE)______$(PINK)88$(WHITE)___$(PINK)88\n\
88$(WHITE)_____________________________$(PINK)88$(WHITE)____$(PINK)888$(WHITE)___$(PINK)88\n\
88$(WHITE)_____________________________$(PINK)88888888$(WHITE)___$(PINK)88\n\
88$(WHITE)______________________________$(PINK)88$(WHITE)__$(PINK)888$(WHITE)____$(PINK)88\n\
88$(WHITE)______________________________$(PINK)888$(WHITE)_$(PINK)88$(WHITE)_____$(PINK)88\n\
88$(WHITE)___________       ___________$(PINK)888$(WHITE)_______$(PINK)88\n\
_88$(WHITE)________________________________$(PINK)88\n\
$(WHITE)__$(PINK)888888888888888888888888888888888"

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