/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 13:06:39 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

static int	render_game(t_cub3d *data)
{
	static double	time;
	
	time += get_delta_time();
	if (time >= 1.0 / FPS)
	{
		player_movement(data, time);
		player_jump(data, time);
		update_mouse_rotation(data, time); // Continuous rotation based on distance from center
		update_keyboard_rotation(data, time); // Keyboard-based rotation using arrow keys
		raycast_render(data);
		mlx_clear_window(data->mlx, data->window);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
		time = 0;
	}
	return (0);
}

void	game_start(t_cub3d *data)
{
	init_game(data);
	// Initialize mouse at center (no forced reset)
	data->mouse.x = data->mouse.cx;
	data->mouse.y = data->mouse.cy;
	raycast_render(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	mlx_hook(data->window, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->window, 3, 1L << 1, key_released, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_moved, data);
	mlx_loop_hook(data->mlx, render_game, data);
	mlx_loop(data->mlx);
}
// adicionei
static int	unified_key_press(int keycode, t_cub3d *data)
{
	if (data->status != GAME)
		return (key_press_handler(keycode, data));
	return (key_pressed(keycode, data));
}

static int	unified_key_release(int keycode, t_cub3d *data)
{
	if (data->status != GAME)
		return (key_release_handler(keycode, data));
	return (key_released(keycode, data));
}

static int	unified_loop(t_cub3d *data)
{
	static int	game_started = 0;

	if (data->status != GAME)
		return (menu_loop_handler(data));
	if (!game_started)
	{
		game_started = 1;
		cleanup_menu(data);
		data->mouse.cx = data->current_width / 2;
		data->mouse.cy = data->current_height / 2;
		mlx_mouse_hide(data->mlx, data->window);
		data->mouse.x = data->mouse.cx;
		data->mouse.y = data->mouse.cy;
		raycast_render(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	}
	return (render_game(data));
}

void	reattach_hooks(t_cub3d *data)
{
	mlx_hook(data->window, 2, 1L << 0, unified_key_press, data);
	mlx_hook(data->window, 3, 1L << 1, unified_key_release, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_moved, data);
	mlx_loop_hook(data->mlx, unified_loop, data);
}

void	run_with_menu(t_cub3d *data)
{
	init_game(data);
	data->current_width = WIDTH;
	data->current_height = HEIGHT;
	mlx_mouse_show(data->mlx, data->window);
	if (init_menu_images(data) == -1)
		exit_error(data, "Failed to load menu images");
	init_menu_state(data);
	render_main_menu(data);
	mlx_hook(data->window, 2, 1L << 0, unified_key_press, data);
	mlx_hook(data->window, 3, 1L << 1, unified_key_release, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_moved, data);
	mlx_loop_hook(data->mlx, unified_loop, data);
	mlx_loop(data->mlx);
}

