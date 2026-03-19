/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:56:34 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/19 00:23:15 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//The scan_patrol_min function scans leftwards 
//to find the left most accessible coordinate on the map.
//It returns the minimum valid X-coordinate reached before encountering
//walls, doors, or empty void spaces.
int	scan_patrol_min(t_cub3d *data, int grid_y, int grid_x)
{
	int	x;

	x = grid_x - 1;
	while (x >= 0 && data->map.grid[grid_y][x] != '1'
		&& data->map.grid[grid_y][x] != 'D'
		&& data->map.grid[grid_y][x] != 'B'
		&& data->map.grid[grid_y][x] != ' ')
		x--;
	return (x + 1);
}

//The scan_patrol_max function performs a similar scan but rightwards
//to find the rightmost accessible X-coordinate on the map for enemy patrol.
int	scan_patrol_max(t_cub3d *data, int grid_y, int grid_x)
{
	int	x;

	x = grid_x + 1;
	while (x < data->map.col_count && data->map.grid[grid_y][x] != '1'
		&& data->map.grid[grid_y][x] != 'D'
		&& data->map.grid[grid_y][x] != 'B'
		&& data->map.grid[grid_y][x] != ' ')
		x++;
	return (x - 1);
}

//Checks if an enemy can move into a given pixel position by 
//converting it to grid coordinates and checking if the block is walkable
int	enemy_can_move(t_cub3d *data, double px, double py)
{
	int	gx;
	int	gy;

	gx = (int)(px / data->tile);
	gy = (int)(py / data->tile);
	if (gx < 0 || gx >= data->map.col_count
		|| gy < 0 || gy >= data->map.row_count)
		return (0);
	if (data->map.grid[gy][gx] == '1')
		return (0);
	if (data->map.grid[gy][gx] == 'B')
		return (0);
	if (data->map.grid[gy][gx] == 'D'
		&& !is_door_open(data, gx, gy))
		return (0);
	return (1);
}

//Moves an enemy towards the player's position if it's in chasing mode,
//calculating the direction vector and applying movement based on speed and delta time.
void	chase_player(t_cub3d *data, t_enemy *enemy, double dt)
{
	double	dx;
	double	dy;
	double	speed;
	double	new_x;
	double	new_y;

	dx = data->player.pos_x - enemy->pos_x;
	dy = data->player.pos_y - enemy->pos_y;
	if (sqrt(dx * dx + dy * dy) < 0.001)
		return ;
	speed = enemy->speed
		* (ENEMY_CHASE_SPEED_MULT * data->game_settings.difficulty_mult);
	new_x = enemy->pos_x + (dx / sqrt(dx * dx + dy * dy)) * speed * dt;
	new_y = enemy->pos_y + (dy / sqrt(dx * dx + dy * dy)) * speed * dt;
	if (enemy_can_move(data, new_x, enemy->pos_y))
		enemy->pos_x = new_x;
	if (enemy_can_move(data, enemy->pos_x, new_y))
		enemy->pos_y = new_y;
}

//Moves an enemy back and forth between its patrol boundaries when not chasing,
//reversing direction when reaching the limits.
void	patrol_enemy(t_cub3d *data, t_enemy *enemy, double dt)
{
	double	new_x;
	double	speed;
	double	min_px;
	double	max_px;

	speed = enemy->speed;
	new_x = enemy->pos_x + enemy->dir * speed * dt;
	min_px = (enemy->patrol_min + 0.5) * data->tile;
	max_px = (enemy->patrol_max + 0.5) * data->tile;
	if (new_x <= min_px || new_x >= max_px)
	{
		enemy->dir *= -1.0;
		if (new_x <= min_px)
			new_x = min_px;
		else
			new_x = max_px;
	}
	enemy->pos_x = new_x;
}
