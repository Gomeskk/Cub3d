
#ifndef CUB3D_H
# define CUB3D_H

# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Libft/libft.h"
# include "../complete_lib/minilibx-linux/mlx.h"
# include "../complete_lib/minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WRONG_ARGC "cub3d: singular map argument expected."
# define WRONG_MAP_NAME "cub3d: .cub argument extended expected."
# define MAP_ERROR "cub3d: map error."
# define WRONG_MAP "cub3d: non acceptable map."
# define NO_IDENTIFIERS "cub3d: non acceptable identifiers."
# define INV_NO "cub3d: invalid or duplicate 'NO'."
# define INV_SO "cub3d: invalid or duplicate 'SO'."
# define INV_EA "cub3d: invalid or duplicate 'EA'."
# define INV_WE "cub3d: invalid or duplicate 'WE'."
# define INV_CEILING "cub3d: invalid or duplicate 'C'."
# define INV_FLOOR "cub3d: invalid or duplicate 'F'."

# define HEIGHT 1080
# define WIDTH 1920
# define TILE_SIZE 64
# define FPS 60

/* typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img; */

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

typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_textures	textures;
	t_status	status;
	t_tiles		tiles;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_mouse		mouse;
}				t_cub3d;

//			PARSER			//
int		check_map_name(char *map);
int		read_map(char *map, t_cub3d *data);

//			FREE			//
void	free_all(t_cub3d *data);




// map
//static int	    count_lines(char *file);
int				load_map(t_map *map, char *file);
void			free_map(t_map *map);
//static int		check_row_all_ones(char *row);
int				validate_map(t_map *map);
//static void		draw_tile_at(t_cub3d *game, int tile_col, int tile_row, int color);
void			render_walls(t_cub3d *game);

#endif