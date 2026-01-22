/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:24:19 by bpires-r          #+#    #+#             */
/*   Updated: 2026/01/04 21:03:35 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	circle_intersects_rectangle(t_cub3d *data, double cx, double cy, int row, int col)
{
	double	rect_x;
	double	rect_y;
	double	dx;
	double	dy;

	rect_x = (double)col * (double)data->tile;
	rect_y = (double)row * (double)data->tile;
	if (cx < rect_x)
		dx = rect_x;
	else if (cx > rect_x + (double)data->tile)
		dx = rect_x + (double)data->tile;
	else
		dx = cx;
	if (cy < rect_y)
		dy = rect_y;
	else if (cy > rect_y + (double)data->tile)
		dy = rect_y + (double)data->tile;
	else
		dy = cy;
	dx = cx - dx;
	dy = cy - dy;
	return (dx * dx + dy * dy <= 
		(double)data->player.radius * (double)data->player.radius);
}

static int	check_collision_range(t_cub3d *data, double cx, double cy, int start_row, int end_row)
{
	int	row;
	int	col;
	int	start_col;
	int	end_col;

	start_col = (int)floor((cx - data->player.radius) / (double)data->tile);
	end_col = floor((cx + data->player.radius) / (double)data->tile);
	if (start_col < 0)
		start_col = 0;
	if (end_col >= data->map.col_count)
		end_col = data->map.col_count - 1;
	row = start_row;
	while (row <= end_row)
	{
		col = start_col;
		while (col <= end_col)
		{
			if (data->map.grid[row][col] == '1' && 
				circle_intersects_rectangle(data, cx, cy, row, col))
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}


int	circle_collides_wall(t_cub3d *data, double cx, double cy)
{
	int	start_row;
	int	end_row;

	start_row = (int)floor((cy - data->player.radius) / (double)data->tile);
	end_row = (int)floor((cy + data->player.radius) / (double)data->tile);
	if (start_row < 0)
		start_row = 0;
	if (end_row >= data->map.row_count)
		end_row = data->map.row_count - 1;
	return (check_collision_range(data, cx, cy, start_row, end_row));
}


static void	calculate_movement_direction(t_cub3d *data, double *dx, double *dy)
{
	*dx = 0.0;
	*dy = 0.0;

	if (data->keys.w)
		*dy -= 1.0;
	if (data->keys.s)
		*dy += 1.0;
	if (data->keys.a)
		*dx -= 1.0;
	if (data->keys.d)
		*dx += 1.0;
	if (*dx != 0.0 && *dy != 0.0)
	{
		*dx *= DIAGONAL_FACTOR;
		*dy *= DIAGONAL_FACTOR;
	}
}

static void	attempt_movement_with_collision(t_cub3d *data, double nx, double ny)
{
	if (!circle_collides_wall(data, nx, ny))
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
		return ;
	}
	if (!circle_collides_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	else if (!circle_collides_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	player_movement(t_cub3d *data, double dt)
{
	double	move_distance;
	double	new_x;
	double	new_y;
	double	direction_x;
	double	direction_y;
	
	if (dt <= 0.0)
		return ;
	move_distance = data->player.speed * dt;
	calculate_movement_direction(data, &direction_x, &direction_y);
	new_x = data->player.pos_x + direction_x * move_distance;
	new_y = data->player.pos_y + direction_y * move_distance;

	attempt_movement_with_collision(data, new_x, new_y);
}
