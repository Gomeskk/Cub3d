/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_toggles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:23:30 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:23:31 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Cycles field of view once per V key press.
** Uses static variable to detect key press edge (prevent continuous toggle).
** Process: Check if V key is pressed and wasn't pressed last frame, then cycle.
*/
void	handle_fov_toggle(t_cub3d *data)
{
	static int	last_v_state;

	if (data->keys.v && !last_v_state)
		cycle_fov(data);
	last_v_state = data->keys.v;
}

/*
** Toggles door interaction and button activation once per E key press.
** Uses static variable to detect key press edge (prevent continuous trigger).
** Process: Check if E key is pressed and wasn't pressed last frame, then
** toggle door and activate button at player position.
*/
void	handle_door_toggle(t_cub3d *data)
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
** TAB = toggle minimap, F = toggle flashlight.
** Uses static variables to detect key press edges (prevent continuous toggle).
** Process: Check each key separately and toggle respective boolean flag.
*/
void	handle_ui_toggles(t_cub3d *data)
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
** Toggles mouse lock on T key press and controls cursor visibility.
** Uses static variable to detect key press edge (prevent continuous toggle).
** locked = mouse locked to center, unlocked = free cursor movement.
** Process: Toggle locked state on T key press. If locked, hide cursor and
** center it, otherwise show cursor. Store last state for edge detection.
*/
void	handle_mouse_lock_toggle(t_cub3d *data)
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
** Calls all toggle functions in sequence to process user input.
** Process: Handle FOV toggle, door/button interaction, UI visibility
** toggles (minimap/flashlight), and mouse lock toggle.
*/
void	handle_game_toggles(t_cub3d *data)
{
	handle_fov_toggle(data);
	handle_door_toggle(data);
	handle_ui_toggles(data);
	handle_mouse_lock_toggle(data);
}
