
#ifndef CUB3D_H
# define CUB3D_H

# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include "defines.h"
# include "structs.h"
# include <math.h>

/* typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img; */

typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	int			tile;
	t_img		img;
	t_textures	textures;
	t_status	status;
	t_tiles		tiles;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_mouse		mouse;
}				t_cub3d;

//			INIT			//
void    init_data(t_cub3d *data);
void	init_game(t_cub3d *data);

//			PARSER			//
int		parse_map(t_cub3d *data);
int		parse_texture(char *s, char **dest);
int		parse_colour(char *s, int *dest, t_cub3d *data);
int		parse_identifiers(t_cub3d *data);

int		check_map_name(char *map);
void	check_spawn(t_cub3d *data, char c, int x, int y);
int		is_closed(t_cub3d *data);
void	indetifier_checker(t_cub3d *data);


//			UTILS			//
int		is_ident_line(char *line);
int 	is_empty_line(const char *s);
void	skip_sp_tb(char *s, int *i);
int		get_tile_size(t_cub3d *data);
double	get_time_in_seconds(void);
double	get_delta_time(void);
void	clear_image(t_img *img, int color);

//			MAP UTILS		//
int		count_lines(char *map);
int		read_map(char *map, t_cub3d *data);
void	copy_line(char **dest, char *src, int max_x);
char	**build_grid(t_cub3d *data);
int		is_map_line(char c);
int 	has_space_neighbor(char **g, int r, int c);

//			2DGAME			//
void	pixel_put(t_img *img, int x, int y, int color);
void	draw_minimap(t_cub3d *data);
void	put_color_tile(t_img *screen, int pos_x, int pos_y, int color, int tile);
void	game_start(t_cub3d *data);
int		circle_collides_wall(t_cub3d *data, double cx, double cy);
void    player_movement(t_cub3d *data, double dt);
void	put_player_dot(t_img *img, int cx, int cy, int radius, int color);
int		key_released(int keycode, t_cub3d *data);
int		key_pressed(int keycode, t_cub3d *data);

//			FREE/ERROR			//
void	free_all(t_cub3d *data);
void	exit_error(t_cub3d *data, char *message);
int		x_window(t_cub3d *data);
void	exit_game(char *end_game, t_cub3d *data);

//			TESTER				//
void	print_rgb(int color);
void 	print_grid(char **grid);

#endif