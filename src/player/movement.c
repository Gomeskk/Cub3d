/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:24:19 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/17 18:47:27 by bpires-r         ###   ########.fr       */
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

void	player_jump(t_cub3d *data, double dt)
{
	double	target_z;
	double	z_change;

	if (dt <= 0.0)
		return ;
	if (data->keys.space && !data->player.is_jumping
		&& data->player.z_offset >= CROUCH_HEIGHT)
	{
		data->player.vertical_velocity = JUMP_VELOCITY;
		data->player.is_jumping = 1;
	}
	if (data->player.is_jumping || data->player.z_offset > 0.0)
	{
		if (data->player.vertical_velocity < 0.0)
			data->player.vertical_velocity -= GRAVITY_FALL * dt;
		else
			data->player.vertical_velocity -= GRAVITY_RISE * dt;
		data->player.z_offset += data->player.vertical_velocity * dt;
		if (data->player.z_offset > MAX_JUMP_HEIGHT)
		{
			data->player.z_offset = MAX_JUMP_HEIGHT;
			data->player.vertical_velocity = 0.0;
		}
		if (data->player.z_offset <= 0.0)
		{
			data->player.z_offset = 0.0;
			data->player.vertical_velocity = 0.0;
			data->player.is_jumping = 0;
		}
	}
	else if (!data->player.is_jumping)
	{
		if (data->keys.ctrl)
			target_z = CROUCH_HEIGHT;
		else
			target_z = 0.0;
		if (data->player.z_offset != target_z)
		{
			z_change = CROUCH_TRANSITION_SPEED * dt;
			if (data->player.z_offset < target_z)
			{
				data->player.z_offset += z_change;
				if (data->player.z_offset > target_z)
					data->player.z_offset = target_z;
			}
			else
			{
				data->player.z_offset -= z_change;
				if (data->player.z_offset < target_z)
					data->player.z_offset = target_z;
			}
		}
	}
}

void	player_movement(t_cub3d *data, double dt)
{
	double	move_distance;
	double	new_x;
	double	new_y;
	double	direction_x;
	double	direction_y;
	double	current_speed;
	double	map_width;
	double	map_height;
	double	radius;

	map_width = data->map.col_count * data->tile;
	map_height = data->map.row_count * data->tile;
	radius = data->player.radius;
	if (dt <= 0.0)
		return ;
	calc_movement_direction(data, &direction_x, &direction_y);
	if (direction_x == 0.0 && direction_y == 0.0)
		return ;
	current_speed = data->player.speed;
	if (data->keys.shift)
		current_speed *= SPRINT_MULTIPLIER;
	if (data->keys.ctrl)
		current_speed = data->player.speed * CROUCH_MULTIPLIER;
	move_distance = current_speed * dt;
	new_x = data->player.pos_x + direction_x * move_distance;
	new_y = data->player.pos_y + direction_y * move_distance;
	if (new_x - radius < 0)
		new_x = radius;
	else if (new_x + radius > map_width)
		new_x = map_width - radius;
	if (new_y - radius < 0)
		new_y = radius;
	else if (new_y + radius > map_height)
		new_y = map_height - radius;
	attempt_movement_with_collision(data, new_x, new_y);
}
