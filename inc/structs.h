#ifndef STRUCTS_H
# define STRUCTS_H

# include "../complete_lib/minilibx-linux/mlx.h"
# include "../complete_lib/minilibx-linux/mlx_int.h"

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
	char	spawn_dir; // spawn direction (N, S, E, W)
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
	int			cx;
	int			cy;
	int			ignore;
} t_mouse; // mouse rotation

typedef enum e_status
{
	MENU,
	DIFFICULTY_LEVEL,
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
	int line_height;       // height of line to draw on screen
	int draw_start;        // lowest pixel to fill
	int draw_end;          // highest pixel to fill
}				t_ray;

#endif