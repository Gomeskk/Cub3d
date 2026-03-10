/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 15:16:19 by joafaust         ###   ########.fr       */
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
	static int		last_v_state = 0;
	static int		last_e_state = 0;
	
	time += get_delta_time();
	if (time >= 1.0 / FPS)
	{
		// FOV cycling with debounce - only trigger on press, not hold
		// Prevents rapid cycling when key is held down
		if (data->keys.v && !last_v_state)
			cycle_fov(data);
		last_v_state = data->keys.v;
		
		// Door toggle with debounce - only trigger on press, not hold
		// Prevents rapid open/close when key is held down
		if (data->keys.e && !last_e_state)
		{
			toggle_door(data);
			// Also check for button activation
			activate_button(data);
		}
		last_e_state = data->keys.e;
		
		// Update player physics and position
		player_movement(data, time);
		player_jump(data, time);
		// Handle rotation from both mouse and keyboard
		update_mouse_rotation(data, time); // Continuous rotation based on distance from center
		update_keyboard_rotation(data, time); // Keyboard-based rotation using arrow keys
		// Render 3D view
		raycast_render(data);
		// Draw minimap overlay in top-left corner
		render_minimap(data);
		// Display rendered frame
		mlx_clear_window(data->mlx, data->window);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
		time = 0;
	}
	return (0);
}

static int	unified_key_press(int keycode, t_cub3d *data)
{
	// In menu: handle menu navigation keys
	if (data->status != GAME)
		return (key_press_handler(keycode, data));
	// In game: handle movement/action keys
	return (key_pressed(keycode, data));
}

static int	unified_key_release(int keycode, t_cub3d *data)
{
	// In menu: handle menu key releases
	if (data->status != GAME)
		return (key_release_handler(keycode, data));
	// In game: handle movement key releases
	return (key_released(keycode, data));
}


static int	unified_loop(t_cub3d *data)
{
	static int	game_started = 0;

	// Still in menu system
	if (data->status != GAME)
		return (menu_loop_handler(data));
	// First time entering game after menu
	if (!game_started)
	{
		game_started = 1;
		// Cleanup menu resources
		cleanup_menu(data);
		// Setup game cursor and mouse tracking
		data->mouse.cx = data->current_width / 2; // Divide by 2 to get center of screen
		data->mouse.cy = data->current_height / 2;// Divide by 2 to get center of screen
		mlx_mouse_hide(data->mlx, data->window);
		data->mouse.x = data->mouse.cx;
		data->mouse.y = data->mouse.cy;
		// Render initial game frame
		raycast_render(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	}
	// Continue game loop
	return (render_game(data));
}

void	game_start(t_cub3d *data)
{
	// Initialize game engine
	init_game(data);
	data->current_width = WIDTH;
	data->current_height = HEIGHT;
	mlx_mouse_show(data->mlx, data->window);
	// Load menu images
	if (init_menu_images(data) == -1)
		exit_error(data, "Failed to load menu images");
	// Initialize menu state and display
	init_menu_state(data);
	render_main_menu(data);
	// Attach unified event hooks (work for both menu and game)
	mlx_hook(data->window, 2, 1L << 0, unified_key_press, data);
	mlx_hook(data->window, 3, 1L << 1, unified_key_release, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_moved, data);
	mlx_loop_hook(data->mlx, unified_loop, data);
	// Start MLX event loop
	mlx_loop(data->mlx);
}

void	reattach_hooks(t_cub3d *data)
{
	// Reattach event hooks after resolution change
	mlx_hook(data->window, 2, 1L << 0, unified_key_press, data);
	mlx_hook(data->window, 3, 1L << 1, unified_key_release, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_hook(data->window, 6, 1L << 6, mouse_moved, data);
	mlx_loop_hook(data->mlx, unified_loop, data);
}

