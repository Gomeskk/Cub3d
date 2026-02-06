/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:19:40 by bpires-r          #+#    #+#             */
/*   Updated: 2026/02/06 16:04:11 by bpires-r         ###   ########.fr       */
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

int mouse_move(int x, int y, t_cub3d *data)
{
    printf("Mouse move called: x=%d, y=%d\n", x, y);
    //pesquisar why x and why y are inverted also why call x and y in this function as parameters?
    int dx;
    double rot_speed = 0.002; // Adjust sensitivity
    
    // Calculate mouse movement
    dx = x - data->mouse.prev_x;
    
    // Rotate player based on horizontal mouse movement
    if (dx != 0)
        rotate_player(&data->player, dx * rot_speed);
    
    // Update mouse position
    data->mouse.prev_x = x;
    data->mouse.prev_y = y;
    data->mouse.x = x;
    data->mouse.y = y;
    printf("Mouse moved dx=%d, rotating by %.4f\n", x, dx * rot_speed);
    return (0);
}