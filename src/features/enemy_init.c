/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:56:28 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 22:56:29 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_enemies(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.enemy_count = 0;
	y = -1;
	while (++y < data->map.row_count)
	{
		x = -1;
		while (++x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'F')
				data->map.enemy_count++;
		}
	}
	if (data->map.enemy_count == 0)
	{
		data->map.enemies = NULL;
		return ;
	}
	data->map.enemies = malloc(sizeof(t_enemy) * data->map.enemy_count);
	if (!data->map.enemies)
		data->map.enemy_count = 0;
}

static void	init_vars(t_cub3d *data, int x, int y, int i)
{
	data->map.enemies[i].grid_x = x;
	data->map.enemies[i].grid_y = y;
	data->map.enemies[i].dir = 1.0;
	data->map.enemies[i].patrol_min = (double)scan_patrol_min(data, y, x);
	data->map.enemies[i].patrol_max = (double)scan_patrol_max(data, y, x);
	data->map.enemies[i].speed = ENEMY_SPEED_BASE
		* data->game_settings.difficulty_mult;
	data->map.enemies[i].vision_radius = ENEMY_VISION_RADIUS
		* data->game_settings.difficulty_mult;
	data->map.enemies[i].chasing = 0;
	data->map.grid[y][x] = '0';
}

void	store_enemy_positions(t_cub3d *data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < data->map.row_count)
	{
		x = -1;
		while (++x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] != 'F')
				continue ;
			init_vars(data, x, y, i);
			i++;
		}
	}
}
