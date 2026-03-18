/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 17:46:51 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Fills every pixel in the target image with the given color.
** img = target image buffer to fill, color = RGB hex color value.
** Process: Iterate through all pixels row by row and set each to the
** specified color using pixel_put function.
*/
void	clear_image(t_img *img, int color)
{
	int	pixel_y;
	int	pixel_x;

	pixel_y = 0;
	while (pixel_y < img->height)
	{
		pixel_x = 0;
		while (pixel_x < img->width)
		{
			pixel_put(img, pixel_x, pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

/*
** Reattaches all window and loop hooks after window recreation.
** Called after resolution change to reconnect event handlers.
** Process: Hook key press/release, window close, mouse movement, and main
** loop handler. Set window event mask and sync display.
*/
void	reattach_hooks(t_cub3d *data)
{
	mlx_hook(data->window, 2, 1L << 0, unified_key_press, data);
	mlx_hook(data->window, 3, 1L << 1, unified_key_release, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_moved, data);
	mlx_loop_hook(data->mlx, unified_loop, data);
	mlx_int_set_win_event_mask(data->mlx);
	mlx_do_sync(data->mlx);
}

/*
** Initializes menu/game state, registers hooks, and starts the mlx loop.
** Entry point to start the game after parsing and setup.
** Process: Initialize game structures, set initial window size, show cursor,
** load menu images, initialize menu state, render main menu, attach all
** event hooks, and start MLX event loop (blocking until exit).
*/
void	game_start(t_cub3d *data)
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
