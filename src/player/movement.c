/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:24:19 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/17 21:10:38 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	keep_player_in_bounds(t_cub3d *data, double *new_x, double *new_y)
{
	if (*new_x - data->player.radius < 0)
		*new_x = data->player.radius;
	else if (*new_x + data->player.radius > data->map.col_count * data->tile)
		*new_x = data->map.col_count * data->tile - data->player.radius;
	if (*new_y - data->player.radius < 0)
		*new_y = data->player.radius;
	else if (*new_y + data->player.radius > data->map.row_count * data->tile)
		*new_y = data->map.row_count * data->tile - data->player.radius;
}

void	player_movement(t_cub3d *data, double dt)
{
	double	speed;
	double	new_x;
	double	new_y;
	double	direction_x;
	double	direction_y;

	if (dt <= 0.0)
		return ;
	calc_movement_direction(data, &direction_x, &direction_y);
	if (direction_x == 0.0 && direction_y == 0.0)
		return ;
	speed = data->player.speed;
	if (data->keys.shift)
		speed *= SPRINT_MULTIPLIER;
	if (data->keys.ctrl)
		speed = data->player.speed * CROUCH_MULTIPLIER;
	speed *= dt;
	new_x = data->player.pos_x + direction_x * speed;
	new_y = data->player.pos_y + direction_y * speed;
	keep_player_in_bounds(data, &new_x, &new_y);
	attempt_movement_with_collision(data, new_x, new_y);
}
