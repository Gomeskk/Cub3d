/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:58:09 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 22:58:10 by bpires-r         ###   ########.fr       */
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
	data->player.plane_x = old_planex
		* cos(angle) - data->player.plane_y * sin(angle);
	data->player.plane_y = old_planex
		* sin(angle) + data->player.plane_y * cos(angle);
}

static void	y_mouse_rotation(t_cub3d *data, double speed,
	double sens, double dt)
{
	double	dist_center;

	dist_center = (double)(data->mouse.y - data->mouse.cy);
	speed = -dist_center * MOUSE_SENSITIVITY * sens * dt * 3000.0;
	data->player.pitch += speed;
	if (data->player.pitch > MAX_PITCH)
		data->player.pitch = MAX_PITCH;
	if (data->player.pitch < -MAX_PITCH)
		data->player.pitch = -MAX_PITCH;
}

void	update_mouse_rotation(t_cub3d *data, double dt)
{
	double	distance_from_center_x;
	double	distance_from_center_y;
	double	rotation_speed;
	double	pitch_speed;
	double	sensibility_mult;

	pitch_speed = 0.0;
	if (!data->mouse.locked)
		return ;
	sensibility_mult
		= get_sensibility_multiplier(data->menu.options.sensibility_level);
	distance_from_center_x = (double)(data->mouse.x - data->mouse.cx);
	distance_from_center_y = (double)(data->mouse.y - data->mouse.cy);
	if (distance_from_center_x != 0.0)
	{
		rotation_speed = distance_from_center_x
			* MOUSE_SENSITIVITY * sensibility_mult * dt;
		rotate_player(data, rotation_speed);
	}
	if (distance_from_center_y != 0.0)
		y_mouse_rotation(data, pitch_speed, sensibility_mult, dt);
	if (distance_from_center_x != 0.0 || distance_from_center_y != 0.0)
		mlx_mouse_move(data->mlx, data->window, data->mouse.cx, data->mouse.cy);
}

int	mouse_moved(int x, int y, t_cub3d *data)
{
	data->mouse.x = x;
	data->mouse.y = y;
	return (0);
}
