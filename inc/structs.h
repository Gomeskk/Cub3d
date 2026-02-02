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

typedef struct s_scale_data
{
	float		scale;
	int			scaled_w;
	int			scaled_h;
	int			bpp;
}				t_scale_data;

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
	char		direction;
}				t_map;

typedef struct s_player
{
	double	pos_y;
	double	pos_x;
	double	speed;
	int		radius;
	double	vel_x;
	double	vel_y;
	// Direction vector (where the player is facing)
	double dir_x;
	double dir_y;
	// Camera plane (perpendicular to direction vector)
	double	plane_x;
	double	plane_y;
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
	MENU_CREDITS,
	DIFFICULTY_SCREEN,
	DIFF_EASY,
	DIFF_MEDIUM,
	DIFF_HARD,
	SKIN_SELECT,
	GAME,
	CREDITS,
}				t_status;

typedef enum e_options_section
{
	SECTION_SOUND,
	SECTION_RESOLUTION,
	SECTION_SENSIBILITY,
}				t_options_section;

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
	t_menu_img	resolution[5];
	t_menu_img	tab_sound;
	t_menu_img	tab_resolution;
	t_menu_img	tab_sensibility;
	t_menu_img	resolution_approve;
	t_menu_img	resolution_decline;
	t_menu_img	screen_buffer;
	int				menu_choice;
	int				difficulty_choice;
	int				sensibility_level;
	int				volume_level;
	int				resolution_level;
	t_options_section	options_section;
	int				resolution_arrow_count;
	int				last_arrow_direction;
	int				resolution_confirm_active;
	int				resolution_confirm_choice;
	int				pending_resolution_level;
}				t_menu;

typedef struct s_game_settings
{
	int			player_health;
	float		enemy_speed_mult;
	float		enemy_damage_mult;
}				t_game_settings;

#endif