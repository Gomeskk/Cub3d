/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:19:49 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:19:50 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns the color for a specific map tile based on its type.
** Walls are cyan, doors are purple (green if open), buttons are yellow.
*/
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

/*
** Draws a single tile on the minimap at the given grid position.
** Skips empty spaces and calculates screen position from params.
** params[0] = tile_size (pixels per tile)
** params[1] = offset (margin from screen edge)
*/
static void	draw_map_tile(t_cub3d *data, int x, int y, int params[2])
{
	int		screen_x;
	int		screen_y;
	int		color;
	int		pos[2];
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == ' ' || tile == '\0')
		return ;
	screen_x = params[1] + x * params[0];
	screen_y = params[1] + y * params[0];
	color = get_tile_color(data, x, y);
	pos[0] = screen_x;
	pos[1] = screen_y;
	put_color_tile(&data->img, pos, color, params[0]);
}

/*
** Iterates through the entire map grid and draws each tile.
** params[0] = tile size, params[1] = offset from screen edge.
*/
void	draw_map_tiles(t_cub3d *data, int params[2])
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
