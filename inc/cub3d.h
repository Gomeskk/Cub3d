
#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <mlx_int.h>
# include <stdlib.h>

# define HEIGHT 1080
# define WIDTH 1920
# define TILE_SIZE 64
# define FPS 60

typedef struct s_tiles
{
	t_img	wall;
	t_img	floor;
}			t_tiles;

typedef struct s_map
{
	char	**map;
	char	**map_cpy;
	int		row_count;
	int		col_count;
}			t_map;

typedef struct s_player
{
	int	pos_y;
	int	pos_x;
}			t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
}			t_keys;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
	int	delta_x;
	int	delta_y;
}			t_mouse; //mouse rotation

typedef enum e_status
{	
    MENU,
	SKIN_SELECT,
	GAME,
	CREDITS,
}			t_status;

typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_status	status;
	t_tiles		tiles;
	t_map		map;
	t_player	player;
	t_keys		keys;
    t_mouse		mouse;
}			t_cub3d;

#endif
