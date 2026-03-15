/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/15 23:48:45 by joafaust         ###   ########.fr       */
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

static void	handle_game_toggles(t_cub3d *data)
{
	static int	last_v_state = 0;
	static int	last_e_state = 0;
	static int	last_tab_state = 0;
	static int	last_t_state = 0;
	static int	last_f_state = 0;

	if (data->keys.v && !last_v_state)
		cycle_fov(data);
	last_v_state = data->keys.v;
	if (data->keys.e && !last_e_state)
	{
		toggle_door(data);
		activate_button(data);
	}
	last_e_state = data->keys.e;
	if (data->keys.tab && !last_tab_state)
		data->player.minimap_visible = !data->player.minimap_visible;
	last_tab_state = data->keys.tab;
	if (data->keys.t && !last_t_state)
	{
		data->mouse.locked = !data->mouse.locked;
		if (data->mouse.locked)
		{
			mlx_mouse_hide(data->mlx, data->window);
			mlx_mouse_move(data->mlx, data->window,
				data->mouse.cx, data->mouse.cy);
			data->mouse.x = data->mouse.cx;
			data->mouse.y = data->mouse.cy;
		}
		else
			mlx_mouse_show(data->mlx, data->window);
	}
	last_t_state = data->keys.t;
	if (data->keys.f && !last_f_state)
		data->player.flashlight_on = !data->player.flashlight_on;
	last_f_state = data->keys.f;
}

static void	render_game_frame(t_cub3d *data, double time)
{
	player_movement(data, time);
	player_jump(data, time);
	update_enemies(data, time);
	check_enemy_detection(data);
	if (check_enemy_collision(data))
		exit_game("An enemy caught you! Game Over!", data);
	update_mouse_rotation(data, time);
	update_keyboard_rotation(data, time);
	raycast_render(data);
	if (data->player.minimap_visible)
		render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	update_fps_counter(&data->fps);
	render_fps(data);
	mlx_do_sync(data->mlx);
}

static int	render_game(t_cub3d *data)
{
	static double	time;

	time += get_delta_time();
	if (time >= 1.0 / FPS)
	{
		handle_game_toggles(data);
		render_game_frame(data, time);
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
		// Apply difficulty settings based on menu choice
		apply_difficulty_settings(data);
		// Cleanup menu resources
		cleanup_menu(data);
		// Setup game cursor and mouse tracking
		data->mouse.cx = data->current_width / 2; // Divide by 2 to get center of screen
		data->mouse.cy = data->current_height / 2;// Divide by 2 to get center of screen
		data->mouse.locked = 1; // Start with mouse locked in game
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
	// CRITICAL: Call mlx_int_set_win_event_mask to apply the hook masks to X11
	// This function collects all hook masks and applies them to the window
	// Normally only called by mlx_loop at startup, but we need it after window recreation
	mlx_int_set_win_event_mask(data->mlx);
	// Force X11 to process the hook registrations
	mlx_do_sync(data->mlx);
}

