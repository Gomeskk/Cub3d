#include "../../inc/cub3d.h"

static void	navigate_menu(t_cub3d *data, int direction)
{
	data->menu.menu_choice += direction;
	if (data->menu.menu_choice < MENU_START)
		data->menu.menu_choice = MENU_CREDITS;
	else if (data->menu.menu_choice > MENU_CREDITS)
		data->menu.menu_choice = MENU_START;
	render_main_menu(data);
}

static void	select_menu_option(t_cub3d *data)
{
	if (data->menu.menu_choice == MENU_START)
	{
		data->status = DIFFICULTY_SCREEN;
		render_difficulty_menu(data);
	}
	else if (data->menu.menu_choice == MENU_OPTIONS)
	{
		data->status = CREDITS;
		render_credits(data);
	}
	else if (data->menu.menu_choice == MENU_CREDITS)
		data->status = GAME;
}

int	handle_main_menu_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
		navigate_menu(data, -1);
	else if (keycode == XK_Down || keycode == XK_s)
		navigate_menu(data, 1);
	else if (keycode == XK_Return)
		select_menu_option(data);
	else if (keycode == XK_Escape)
		exit(0);
	return (0);
}

static void	change_difficulty(t_cub3d *data, int direction)
{
	data->menu.difficulty_choice += direction;
	if (data->menu.difficulty_choice > DIFF_HARD)
		data->menu.difficulty_choice = DIFF_EASY;
	else if (data->menu.difficulty_choice < DIFF_EASY)
		data->menu.difficulty_choice = DIFF_HARD;
	render_difficulty_menu(data);
}

int	handle_difficulty_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
		change_difficulty(data, 1);
	else if (keycode == XK_Down || keycode == XK_s)
		change_difficulty(data, -1);
	else if (keycode == XK_Return || keycode == XK_Escape)
	{
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		render_main_menu(data);
	}
	return (0);
}

int	handle_credits_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
	{
		if (data->menu.options.resolution_confirm_active)
		{
			data->menu.options.resolution_confirm_active = 0;
			render_credits(data);
			return (0);
		}
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		data->menu.options.section = SECTION_SOUND;
		render_main_menu(data);
	}
	else if (keycode == XK_Return)
		handle_enter_key(data);
	else if (keycode == XK_Tab)
	{
		data->menu.options.section = (data->menu.options.section + 1) % SECTION_COUNT;
		render_credits(data);
	}
	else if (keycode == XK_Left || keycode == XK_a
		|| keycode == XK_Right || keycode == XK_d)
		handle_horizontal_keys(keycode, data);
	else if (keycode == XK_Up || keycode == XK_w
		|| keycode == XK_Down || keycode == XK_s)
		handle_vertical_keys(keycode, data);
	return (0);
}

int	menu_key_handler(int keycode, t_cub3d *data)
{
	if (data->status == MAIN_MENU_SCREEN)
		return (handle_main_menu_keys(keycode, data));
	else if (data->status == DIFFICULTY_SCREEN)
		return (handle_difficulty_keys(keycode, data));
	else if (data->status == CREDITS)
		return (handle_credits_keys(keycode, data));
	return (0);
}
