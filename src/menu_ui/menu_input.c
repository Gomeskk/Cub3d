/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:18:08 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:18:09 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Update movement key state for menu navigation keys.
*/
static void	set_key_state(int keycode, t_cub3d *data, int state)
{
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = state;
	else if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = state;
	else if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = state;
	else if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = state;
}

/*
** Handle key press events and dispatch special menu keys.
*/
int	key_press_handler(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape && data->status == MAIN_MENU_SCREEN)
		exit(0);
	set_key_state(keycode, data, 1);
	if (keycode == XK_Return || keycode == XK_Tab || keycode == XK_Escape)
		return (menu_key_handler(keycode, data));
	return (0);
}

int	key_release_handler(int keycode, t_cub3d *data)
{
	set_key_state(keycode, data, 0);
	return (0);
}

/*
** Handle key inputs on credits screen
** Escape: back to main menu
*/
int	handle_credits_screen_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
	{
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		render_main_menu(data);
	}
	return (0);
}

/*
** Top-level menu key dispatcher
** Routes key events to appropriate handler based on current menu status
*/
int	menu_key_handler(int keycode, t_cub3d *data)
{
	if (data->status == MAIN_MENU_SCREEN)
		return (handle_main_menu_keys(keycode, data));
	else if (data->status == DIFFICULTY_SCREEN)
		return (handle_difficulty_keys(keycode, data));
	else if (data->status == SKIN_SELECT)
		return (handle_skin_select_keys(keycode, data));
	else if (data->status == OPTIONS_SCREEN)
		return (handle_options_screen_keys(keycode, data));
	else if (data->status == CREDITS_SCREEN)
		return (handle_credits_screen_keys(keycode, data));
	return (0);
}
