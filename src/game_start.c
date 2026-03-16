/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/15 23:51:26 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Fills every pixel in the target image with the given color.
*/
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

/*
** Cycles field of view once per V key press.
*/
static void	handle_fov_toggle(t_cub3d *data)
{
	static int	last_v_state;

	if (data->keys.v && !last_v_state)
		cycle_fov(data);
	last_v_state = data->keys.v;
}

/*
** Toggles door interaction and button activation once per E key press.
*/
static void	handle_door_toggle(t_cub3d *data)
{
	static int	last_e_state;

	if (data->keys.e && !last_e_state)
	{
		toggle_door(data);
		activate_button(data);
	}
	last_e_state = data->keys.e;
}

/*
** Toggles minimap and flashlight visibility on key press edges.
*/
static void	handle_ui_toggles(t_cub3d *data)
{
	static int	last_tab_state;
	static int	last_f_state;

	if (data->keys.tab && !last_tab_state)
		data->player.minimap_visible = !data->player.minimap_visible;
	last_tab_state = data->keys.tab;
	if (data->keys.f && !last_f_state)
		data->player.flashlight_on = !data->player.flashlight_on;
	last_f_state = data->keys.f;
}

/*
** Toggles mouse lock on T and recenters cursor when lock is enabled.
*/
static void	handle_mouse_lock_toggle(t_cub3d *data)
{
	static int	last_t_state;

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
}

/*
** Executes all gameplay toggle handlers for the current frame.
*/
static void	handle_game_toggles(t_cub3d *data)
{
	handle_fov_toggle(data);
	handle_door_toggle(data);
	handle_ui_toggles(data);
	handle_mouse_lock_toggle(data);
}

/*
** Updates player/world state and renders a complete gameplay frame.
*/
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

/*
** Runs the gameplay loop at the configured FPS cadence.
*/
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

/*
** Routes key press events to menu or gameplay handlers.
*/
static int	unified_key_press(int keycode, t_cub3d *data)
{
	if (data->status != GAME)
		return (key_press_handler(keycode, data));
	return (key_pressed(keycode, data));
}

/*
** Routes key release events to menu or gameplay handlers.
*/
static int	unified_key_release(int keycode, t_cub3d *data)
{
	if (data->status != GAME)
		return (key_release_handler(keycode, data));
	return (key_released(keycode, data));
}

/*
** Runs menu loop until GAME starts, then initializes first game frame.
*/
static int	unified_loop(t_cub3d *data)
{
	static int	game_started = 0;

	if (data->status != GAME)
		return (menu_loop_handler(data));
	if (!game_started)
	{
		game_started = 1;
		apply_difficulty_settings(data);
		cleanup_menu(data);
		data->mouse.cx = data->current_width / 2;
		data->mouse.cy = data->current_height / 2;
		data->mouse.locked = 1;
		mlx_mouse_hide(data->mlx, data->window);
		data->mouse.x = data->mouse.cx;
		data->mouse.y = data->mouse.cy;
		raycast_render(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	}
	return (render_game(data));
}

/*
** Initializes menu/game state, registers hooks, and starts the mlx loop.
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

/*
** Reattaches all window and loop hooks after window recreation.
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
