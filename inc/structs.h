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

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
}				t_door;

typedef struct s_button
{
	int		x;
	int		y;
	int		is_activated;
}				t_button;

typedef struct s_map
{
	char		**map;
	char		**grid;
	int			start;
	int			row_count;
	int			col_count;
	int			start_point;
	t_door		*doors;
	int			door_count;
	t_button	*buttons;
	int			button_count;
}				t_map;

typedef struct s_player
{
	double	pos_y;
	double	pos_x;
	double	speed;
	int		radius;
	double	vel_x;
	double	vel_y;
	double	angle; //current viewing dir in radians
	double	dir_x; // direction vector
	double	dir_y;
	double	plane_x; // camera plane (for raycast lol)
	double	plane_y;
	double	pitch; // vertical look angle for up/down
	double	z_offset; // vertical position for jumping
	double	vertical_velocity; // current upward/downward velocity
	int		is_jumping; // 1 if in air, 0 if on ground
	int		fov_level; // 0=normal, 1=narrow, 2=wide
	char	spawn_dir; // spawn direction (N, S, E, W)
}				t_player;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			shift;
	int			space;
	int			v;
	int			e;
	int			arrow_up;
	int			arrow_down;
	int			arrow_left;
	int			arrow_right;
}				t_keys;

typedef struct s_mouse
{
	int			x;
	int			y;
	int			cx;
	int			cy;
	int			ignore;
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
	OPTIONS_SCREEN,
	CREDITS_SCREEN,
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
	char		*button;
	char		*alt_texture;
}				t_textures;

typedef struct s_wall_textures
{
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	t_img		door;
	t_img		button;
	t_img		alt_north;
	t_img		alt_south;
	t_img		alt_east;
	t_img		alt_west;
	int			textures_swapped;
}				t_wall_textures;

typedef struct s_ray
{
	double camera_x;       // x-coordinate in camera space (-1 to +1)
	double ray_dir_x;      // ray direction vector x
	double ray_dir_y;      // ray direction vector y
	double delta_dist_x;   // distance ray travels for 1 x-unit
	double delta_dist_y;   // distance ray travels for 1 y-unit
	double side_dist_x;    // distance to next x-side
	double side_dist_y;    // distance to next y-side
	double perp_wall_dist; // perpendicular distance to wall
	int map_x;             // which box of the map we're in (x)
	int map_y;             // which box of the map we're in (y)
	int step_x;            // what direction to step in x (-1 or +1)
	int step_y;            // what direction to step in y (-1 or +1)
	int hit;               // was there a wall hit?
	int side;              // was it a NS or EW wall hit? (0=NS, 1=EW)
	int hit_door;          // did we hit a door?
	int hit_button;        // did we hit a button?
	int line_height;       // height of line to draw on screen
	int draw_start;        // lowest pixel to fill
	int draw_end;          // highest pixel to fill
}				t_ray;

typedef struct s_tex_draw
{
	t_ray	*ray;
	double	step;
	double	tex_pos;
	int		tex_x;
}				t_tex_draw;

typedef struct s_menu_screens
{
	t_menu_img	start_normal;
	t_menu_img	start_hover;
	t_menu_img	start_selected;
	t_menu_img	options_screen;
	t_menu_img	credits_screen;
	t_menu_img	screen_buffer;
	t_menu_img	arrow_up;
	t_menu_img	arrow_down;
	t_menu_img	skin_select;
	t_menu_img	arrow_left;
	t_menu_img	arrow_right;
}				t_menu_screens;

typedef struct s_difficulty_imgs
{
	t_menu_img	easy;
	t_menu_img	medium;
	t_menu_img	hard;
}				t_difficulty_imgs;

typedef struct s_options_imgs
{
	t_menu_img	volume[15];
	t_menu_img	sensibility[5];
	t_menu_img	resolution[5];
	t_menu_img	tab_sound;
	t_menu_img	tab_resolution;
	t_menu_img	tab_sensibility;
	t_menu_img	resolution_approve;
	t_menu_img	resolution_decline;
}				t_options_imgs;

typedef struct s_options_state
{
	t_options_section	section;
	int					volume_level;
	int					sensibility_level;
	int					resolution_level;
	int					resolution_arrow_count;
	int					last_arrow_direction;
	int					resolution_confirm_active;
	int					resolution_confirm_choice;
	int					pending_resolution_level;
}				t_options_state;

typedef struct s_menu
{
	t_menu_screens		screens;
	t_difficulty_imgs	difficulty;
	t_options_imgs		options_imgs;
	t_options_state		options;
	int					menu_choice;
	int					difficulty_choice;
	int					skin_choice;
	int					last_skin_arrow_direction;
}				t_menu;

typedef struct s_game_settings
{
	int			player_health;
	float		enemy_speed_mult;
	float		enemy_damage_mult;
}				t_game_settings;

#endif