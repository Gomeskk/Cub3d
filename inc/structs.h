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

#endif