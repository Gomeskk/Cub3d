/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:58:01 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 22:58:02 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_movement_keys_press(int keycode, t_cub3d *data)
{
	if (keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_d)
		data->keys.d = 1;
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		data->keys.shift = 1;
	if (keycode == XK_Control_L || keycode == XK_Control_R)
		data->keys.ctrl = 1;
	if (keycode == XK_space)
		data->keys.space = 1;
}

int	key_pressed(int keycode, t_cub3d *data)
{
	update_movement_keys_press(keycode, data);
	if (keycode == XK_Escape)
		x_window(data);
	if (keycode == XK_v)
		data->keys.v = 1;
	if (keycode == XK_e)
		data->keys.e = 1;
	if (keycode == XK_Tab)
		data->keys.tab = 1;
	if (keycode == XK_t)
		data->keys.t = 1;
	if (keycode == XK_Up)
		data->keys.arrow_up = 1;
	if (keycode == XK_Down)
		data->keys.arrow_down = 1;
	if (keycode == XK_Left)
		data->keys.arrow_left = 1;
	if (keycode == XK_Right)
		data->keys.arrow_right = 1;
	if (keycode == XK_f)
		data->keys.f = 1;
	return (0);
}

static void	update_movement_keys_release(int keycode, t_cub3d *data)
{
	if (keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_d)
		data->keys.d = 0;
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		data->keys.shift = 0;
	if (keycode == XK_Control_L || keycode == XK_Control_R)
		data->keys.ctrl = 0;
	if (keycode == XK_space)
		data->keys.space = 0;
}

int	key_released(int keycode, t_cub3d *data)
{
	update_movement_keys_release(keycode, data);
	if (keycode == XK_v)
		data->keys.v = 0;
	if (keycode == XK_e)
		data->keys.e = 0;
	if (keycode == XK_Tab)
		data->keys.tab = 0;
	if (keycode == XK_t)
		data->keys.t = 0;
	if (keycode == XK_Up)
		data->keys.arrow_up = 0;
	if (keycode == XK_Down)
		data->keys.arrow_down = 0;
	if (keycode == XK_Left)
		data->keys.arrow_left = 0;
	if (keycode == XK_Right)
		data->keys.arrow_right = 0;
	if (keycode == XK_f)
		data->keys.f = 0;
	return (0);
}
