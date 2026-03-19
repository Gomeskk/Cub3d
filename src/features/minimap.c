/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:20:11 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/19 20:15:52 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Draws a circle outline representing an enemy's vision radius.
** Uses 360 angle steps to create a smooth circular outline.
** enemy_x/enemy_y = enemy center position on screen (in pixels)
** radius_px = vision radius in pixels
** Process: Draw circle by calculating points at each degree (0-359), convert
** degrees to radians for trigonometric functions, calculate point on circle
** using cos/sin, then draw pixel if within screen bounds.
*/
static void	draw_enemy_vision(t_cub3d *data, int enemy_x, int enemy_y,
	int radius_px)
{
	int		angle_deg;
	double	angle_rad;
	int		circle_x;
	int		circle_y;

	angle_deg = 0;
	while (angle_deg < 360)
	{
		angle_rad = angle_deg * M_PI / 180.0;
		circle_x = enemy_x + (int)(cos(angle_rad) * radius_px);
		circle_y = enemy_y + (int)(sin(angle_rad) * radius_px);
		if (circle_x >= 0 && circle_x < data->current_width
			&& circle_y >= 0 && circle_y < data->current_height)
			pixel_put(&data->img, circle_x, circle_y, 0xFF0000);
		angle_deg++;
	}
}

/*
** Draws a single enemy on the minimap with vision radius circle.
** Calculates enemy screen position and displays with yellow dot.
** params[1] = offset, params[2] = map_scale_x1000
** enemy_index = which enemy in the enemies array to draw
** Process: Convert enemy world position to minimap screen position, convert
** vision radius from grid units to screen pixels, draw red circle showing
** vision radius, then draw yellow dot at enemy position (0xFCF803).
*/
static void	draw_enemy_on_map(t_cub3d *data, int params[3], int enemy_index)
{
	int	enemy_screen_x;
	int	enemy_screen_y;
	int	vision_radius_px;

	enemy_screen_x = params[1] + (int)(data->map.enemies[enemy_index].pos_x
			* params[2] / 1000.0);
	enemy_screen_y = params[1] + (int)(data->map.enemies[enemy_index].pos_y
			* params[2] / 1000.0);
	vision_radius_px = (int)(data->map.enemies[enemy_index].vision_radius
			* data->tile * params[2] / 1000.0);
	draw_enemy_vision(data, enemy_screen_x, enemy_screen_y, vision_radius_px);
	put_player_dot(&data->img, enemy_screen_x, enemy_screen_y, 0xFCF803);
}

/*
** Iterates through all enemies and draws them on the minimap.
** Each enemy is shown with vision radius and position marker.
** params contains minimap scaling and offset information.
** Process: Loop through all enemies in the map and draw each one.
*/
static void	draw_enemies_on_map(t_cub3d *data, int params[3])
{
	int	enemy_index;

	enemy_index = 0;
	while (enemy_index < data->map.enemy_count)
	{
		draw_enemy_on_map(data, params, enemy_index);
		enemy_index++;
	}
}

/*
** Prepares minimap rendering parameters based on current screen/map size.
** params[0] = minimap tile size, params[1] = screen offset,
** params[2] = minimap scale * 1000.
*/
static void	init_minimap_params(t_cub3d *data, int params[3],
	int *player_line_len)
{
	int	tile_size;
	int	max_map_size;
	int	screen_offset;

	tile_size = data->current_width / 128;
	if (tile_size < 5)
		tile_size = 5;
	max_map_size = data->current_width / 8;
	if (data->map.col_count > 0
		&& tile_size * data->map.col_count > max_map_size)
		tile_size = max_map_size / data->map.col_count;
	if (data->map.row_count > 0
		&& tile_size * data->map.row_count > max_map_size)
		tile_size = max_map_size / data->map.row_count;
	if (tile_size < 1)
		tile_size = 1;
	screen_offset = data->current_width / 160;
	if (screen_offset < 5)
		screen_offset = 5;
	*player_line_len = tile_size + 3;
	params[0] = tile_size;
	params[1] = screen_offset;
	params[2] = (int)(((double)tile_size / data->tile) * 1000);
}

/*
** Renders the complete minimap: tiles, enemies, and player FOV.
*/
void	render_minimap(t_cub3d *data)
{
	int	player_line_len;
	int	render_params[3];

	init_minimap_params(data, render_params, &player_line_len);
	draw_map_tiles(data, render_params);
	draw_enemies_on_map(data, render_params);
	render_params[0] = player_line_len;
	draw_player_on_map(data, render_params);
}
