
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
	int		pos[2];
	int		i;
	int		edge[4];
	int		j;
	double	t;

	pos[0] = params[1] + (int)(data->player.pos_x * params[2] / 1000.0);
	pos[1] = params[1] + (int)(data->player.pos_y * params[2] / 1000.0);
	i = -1;
	while (++i <= params[0])
	{
		edge[0] = pos[0] + (int)((data->player.dir_x - data->player.plane_x) * i);
		edge[1] = pos[1] + (int)((data->player.dir_y - data->player.plane_y) * i);
		edge[2] = pos[0] + (int)((data->player.dir_x + data->player.plane_x) * i);
		edge[3] = pos[1] + (int)((data->player.dir_y + data->player.plane_y) * i);
		j = -1;
		while (++j <= 20)
		{
			t = j / 20.0;
			pixel_put(&data->img, edge[0] + (int)((edge[2] - edge[0]) * t),
				edge[1] + (int)((edge[3] - edge[1]) * t), 0xdb6cea);
		}
	}
	put_player_dot(&data->img, pos[0], pos[1], 3, 0xFF0000);
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
