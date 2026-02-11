/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:19:40 by bpires-r          #+#    #+#             */
/*   Updated: 2026/02/11 02:14:09 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
		x_window(data);
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = 1;
	return (0);
}

int	key_released(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = 0;
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

void	handle_mouse_rotation(t_cub3d *data, int x)
{
	int center_x = data->current_width / 2;
	int center_y = data->current_height / 2;
	double sens = 0.002;
	int dx = x - center_x;
	rotate_player(&data->player, dx * sens);

	mlx_mouse_move(data->mlx, data->window, center_x, center_y);
}