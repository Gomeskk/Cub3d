
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
			return (0x8704E4);
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

static double	minimap_ray_dist(t_cub3d *data, double ray_dx, double ray_dy)
{
	double	pos_x;
	double	pos_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;

	pos_x = data->player.pos_x / data->tile;
	pos_y = data->player.pos_y / data->tile;
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	if (ray_dx == 0)
		delta_x = 1e30;
	else
		delta_x = fabs(1.0 / ray_dx);
	if (ray_dy == 0)
		delta_y = 1e30;
	else
		delta_y = fabs(1.0 / ray_dy);
	if (ray_dx < 0)
	{
		step_x = -1;
		side_x = (pos_x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_x = (map_x + 1.0 - pos_x) * delta_x;
	}
	if (ray_dy < 0)
	{
		step_y = -1;
		side_y = (pos_y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_y = (map_y + 1.0 - pos_y) * delta_y;
	}
	while (1)
	{
		if (side_x < side_y)
		{
			map_x += step_x;
			if (map_x < 0 || map_x >= data->map.col_count)
				return (side_x);
			if (data->map.grid[map_y][map_x] == '1'
				|| (data->map.grid[map_y][map_x] == 'D'
					&& !is_door_open(data, map_x, map_y)))
				return (side_x);
			side_x += delta_x;
		}
		else
		{
			map_y += step_y;
			if (map_y < 0 || map_y >= data->map.row_count)
				return (side_y);
			if (data->map.grid[map_y][map_x] == '1'
				|| (data->map.grid[map_y][map_x] == 'D'
					&& !is_door_open(data, map_x, map_y)))
				return (side_y);
			side_y += delta_y;
		}
	}
}

static void	draw_minimap_line(t_img *img, int x0, int y0, int x1, int y1,
	int color)
{
	int		steps;
	double	sx;
	double	sy;
	int		i;

	steps = abs(x1 - x0);
	if (abs(y1 - y0) > steps)
		steps = abs(y1 - y0);
	if (steps == 0)
		return ;
	sx = (double)(x1 - x0) / steps;
	sy = (double)(y1 - y0) / steps;
	i = -1;
	while (++i <= steps)
		pixel_put(img, x0 + (int)(sx * i), y0 + (int)(sy * i), color);
}

static void	draw_player_on_map(t_cub3d *data, int params[3])
{
	int		pos[2];
	int		num_rays;
	int		r;
	double	cam_x;
	double	ray_dx;
	double	ray_dy;
	double	dist;
	int		hit[2];

	pos[0] = params[1] + (int)(data->player.pos_x * params[2] / 1000.0);
	pos[1] = params[1] + (int)(data->player.pos_y * params[2] / 1000.0);
	num_rays = 60;
	r = -1;
	while (++r <= num_rays)
	{
		cam_x = 2.0 * r / (double)num_rays - 1.0;
		ray_dx = data->player.dir_x + data->player.plane_x * cam_x;
		ray_dy = data->player.dir_y + data->player.plane_y * cam_x;
		dist = minimap_ray_dist(data, ray_dx, ray_dy);
		hit[0] = pos[0] + (int)(ray_dx * dist * data->tile
				* params[2] / 1000.0);
		hit[1] = pos[1] + (int)(ray_dy * dist * data->tile
				* params[2] / 1000.0);
		draw_minimap_line(&data->img, pos[0], pos[1],
			hit[0], hit[1], 0xdb6cea);
	}
	put_player_dot(&data->img, pos[0], pos[1], 3, 0xfc03d2);
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
	// Draw enemies on minimap with vision radius circle and dot
	{
		int ei = 0;
		while (ei < data->map.enemy_count)
		{
			int ex = params[1] + (int)(data->map.enemies[ei].pos_x
					* params[2] / 1000.0);
			int ey = params[1] + (int)(data->map.enemies[ei].pos_y
					* params[2] / 1000.0);
			int radius_px = (int)(data->map.enemies[ei].vision_radius
					* data->tile * params[2] / 1000.0);
			// Draw vision radius circle outline
			{
				int angle_step = 0;
				while (angle_step < 360)
				{
					double rad = angle_step * M_PI / 180.0;
					int cx = ex + (int)(cos(rad) * radius_px);
					int cy = ey + (int)(sin(rad) * radius_px);
					if (cx >= 0 && cx < data->current_width
						&& cy >= 0 && cy < data->current_height)
						pixel_put(&data->img, cx, cy, 0xFF0000);
					angle_step++;
				}
			}
			put_player_dot(&data->img, ex, ey, 3, 0xFCF803);
			ei++;
		}
	}
	params[0] = line_len;
	draw_player_on_map(data, params);
}
