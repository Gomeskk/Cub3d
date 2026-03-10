
#include "cub3d.h"

static int	get_tile_color(t_cub3d *data, int x, int y)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == '1')
		return (0x00FFFF);
	else if (tile == 'D')
	{
		if (is_door_open(data, x, y))
			return (0x00FF00);
		else
			return (data->textures.ceiling);
	}
	else if (tile == 'B')
		return (0xFFFF00);
	else if (tile == '0' || tile == 'N' || tile == 'S' 
		|| tile == 'E' || tile == 'W')
		return (0x000000);
	return (0x000000);
}

static void	draw_map_tile(t_cub3d *data, int x, int y, int params[2])
{
	int		screen_x;
	int		screen_y;
	int		color;
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == ' ' || tile == '\0')
		return ;
	screen_x = params[1] + x * params[0];
	screen_y = params[1] + y * params[0];
	color = get_tile_color(data, x, y);
	put_color_tile(&data->img, screen_x, screen_y, color, params[0]);
}

static void	draw_map_tiles(t_cub3d *data, int params[2])
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			draw_map_tile(data, x, y, params);
			x++;
		}
		y++;
	}
}

static void	draw_player_on_map(t_cub3d *data, int params[3])
{
	int		px;
	int		py;
	int		i;
	double	map_scale;

	map_scale = (double)params[2] / 1000.0;
	px = params[1] + (int)(data->player.pos_x * map_scale);
	py = params[1] + (int)(data->player.pos_y * map_scale);
	put_player_dot(&data->img, px, py, 3, 0xFF0000);
	i = 0;
	while (i <= params[0])
	{
		pixel_put(&data->img, px + (int)(data->player.dir_x * i),
			py + (int)(data->player.dir_y * i), 0x00FF00);
		i++;
	}
}

void	render_minimap(t_cub3d *data)
{
	int		map_tile;
	int		offset;
	int		line_len;
	int		params[3];
	double	map_scale;

	map_tile = data->current_width / 128;
	if (map_tile < 5)
		map_tile = 5;
	offset = data->current_width / 160;
	if (offset < 5)
		offset = 5;
	line_len = map_tile + 3;
	map_scale = (double)map_tile / data->tile;
	params[0] = map_tile;
	params[1] = offset;
	params[2] = (int)(map_scale * 1000);
	draw_map_tiles(data, params);
	params[0] = line_len;
	draw_player_on_map(data, params);
}
