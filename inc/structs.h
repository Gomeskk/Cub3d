#ifndef STRUCTS_H
# define STRUCTS_H

# include "../complete_lib/minilibx-linux/mlx.h"
# include "../complete_lib/minilibx-linux/mlx_int.h"

typedef struct s_menu_img
{
	void		*image;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_menu_img;

typedef struct s_tiles
{
	t_img		wall;
	t_img		floor;
}				t_tiles;

typedef struct s_map
{
	char		**map;
	char		**grid;
	int			start;
	int			row_count;
	int			col_count;
	int			start_point;
}				t_map;

typedef struct s_player
{
	int			pos_y;
	int			pos_x;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
}				t_keys;

typedef struct s_mouse
{
	int			x;
	int			y;
	int			prev_x;
	int			prev_y;
} t_mouse; // mouse rotation

typedef enum e_status
{
	MAIN_MENU_SCREEN,
	MENU_START,
	MENU_OPTIONS,
	MENU_EXIT,
	DIFFICULTY_SCREEN,
	DIFF_EASY,
	DIFF_MEDIUM,
	DIFF_HARD,
	SKIN_SELECT,
	GAME,
	CREDITS,
}				t_status;

typedef	struct s_textures
{
	int			floor;
	int			ceiling;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_textures;

typedef struct s_menu
{
	t_menu_img	start_normal;
	t_menu_img	start_hover;
	t_menu_img	start_selected;
	t_menu_img	diff_easy;
	t_menu_img	diff_medium;
	t_menu_img	diff_hard;
	t_menu_img	arrow_up;
	t_menu_img	arrow_down;
	t_menu_img	options_screen;
	t_menu_img	credits_screen;
	t_menu_img	volume[15];
	t_menu_img	sensibility[5];
	t_menu_img	tab_sound;
	t_menu_img	tab_resolution;
	t_menu_img	tab_sensibility;
	int			menu_choice;
	int			difficulty_choice;
	int			sensibility_level;
	int			volume_level;
	int			resolution_level;
	int			options_section;
}				t_menu;

typedef struct s_game_settings
{
	int			player_health;
	float		enemy_speed_mult;
	float		enemy_damage_mult;
}				t_game_settings;

#endif