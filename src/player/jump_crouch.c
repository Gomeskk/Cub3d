/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_crouch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:21:06 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:21:07 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_airborne_state(t_cub3d *data, double dt)
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

static void	update_crouch_state(t_cub3d *data, double dt)
{
	double	target_z;
	double	z_change;

	target_z = 0.0;
	if (data->keys.ctrl)
		target_z = CROUCH_HEIGHT;
	if (data->player.z_offset != target_z)
	{
		z_change = CROUCH_TRANSITION_SPEED * dt;
		if (data->player.z_offset < target_z)
			data->player.z_offset += z_change;
		else
			data->player.z_offset -= z_change;
		if ((data->player.z_offset > target_z && data->keys.ctrl)
			|| (data->player.z_offset < target_z && !data->keys.ctrl))
			data->player.z_offset = target_z;
	}
}

void	player_jump(t_cub3d *data, double dt)
{
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
		update_airborne_state(data, dt);
		return ;
	}
	update_crouch_state(data, dt);
}
