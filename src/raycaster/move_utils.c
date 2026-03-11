/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:19:40 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 15:16:19 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
		x_window(data);
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
	if (keycode == XK_v)
		data->keys.v = 1;
	if (keycode == XK_e)
		data->keys.e = 1;
	if (keycode == XK_Tab)
		data->keys.tab = 1;
	if (keycode == XK_Up)
		data->keys.arrow_up = 1;
	if (keycode == XK_Down)
		data->keys.arrow_down = 1;
	if (keycode == XK_Left)
		data->keys.arrow_left = 1;
	if (keycode == XK_Right)
		data->keys.arrow_right = 1;
	return (0);
}

int	key_released(int keycode, t_cub3d *data)
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
	if (keycode == XK_v)
		data->keys.v = 0;
	if (keycode == XK_e)
		data->keys.e = 0;
	if (keycode == XK_Tab)
		data->keys.tab = 0;
	if (keycode == XK_Up)
		data->keys.arrow_up = 0;
	if (keycode == XK_Down)
		data->keys.arrow_down = 0;
	if (keycode == XK_Left)
		data->keys.arrow_left = 0;
	if (keycode == XK_Right)
		data->keys.arrow_right = 0;
	return (0);
}

double get_time_in_seconds(void)
{
    struct timespec ts;
    clock_gettime(1, &ts);
    return (ts.tv_sec + ts.tv_nsec / 1e9);
}

double get_delta_time(void)
{
    static double last = 0.0;
    double now = get_time_in_seconds();

    if (last == 0.0) {
        last = now;
        return 0.0;
    }
    double dt = now - last;
    last = now;
    return dt;
}
