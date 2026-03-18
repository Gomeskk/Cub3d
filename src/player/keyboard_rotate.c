/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:21:22 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:21:23 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_cub3d *data, double angle)
{
	double	old_dirx;
	double	old_diry;
	double	old_planex;

	old_dirx = data->player.dir_x;
	old_diry = data->player.dir_y;
	old_planex = data->player.plane_x;
	data->player.dir_x = old_dirx * cos(angle) - old_diry * sin(angle);
	data->player.dir_y = old_dirx * sin(angle) + old_diry * cos(angle);
	data->player.plane_x = old_planex * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_planex * sin(angle)
		+ data->player.plane_y * cos(angle);
}

static void	up_down(t_cub3d *data, double dt, int max_pitch_scaled)
{
	double	pitch_speed;

	pitch_speed = 0;
	if (data->keys.arrow_up)
	{
		pitch_speed = 500.0 * dt;
		data->player.pitch += pitch_speed;
		if (data->player.pitch > max_pitch_scaled)
			data->player.pitch = max_pitch_scaled;
	}
	if (data->keys.arrow_down)
	{
		pitch_speed = -500.0 * dt;
		data->player.pitch += pitch_speed;
		if (data->player.pitch < -max_pitch_scaled)
			data->player.pitch = -max_pitch_scaled;
	}
}

static void	left_right(t_cub3d *data, double dt)
{
	double	rotation_speed;

	rotation_speed = 0;
	if (data->keys.arrow_left)
	{
		rotation_speed = -2.0 * dt;
		rotate_player(data, rotation_speed);
	}
	if (data->keys.arrow_right)
	{
		rotation_speed = 2.0 * dt;
		rotate_player(data, rotation_speed);
	}
}

void	update_keyboard_rotation(t_cub3d *data, double dt)
{
	double	max_pitch_scaled;

	max_pitch_scaled = MAX_PITCH * ((double)data->current_height
			/ (double)RES_4_HEIGHT);
	if (data->keys.arrow_left || data->keys.arrow_right)
		left_right(data, dt);
	if (data->keys.arrow_up || data->keys.arrow_down)
		up_down(data, dt, max_pitch_scaled);
}
