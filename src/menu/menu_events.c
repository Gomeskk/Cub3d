#include "../../inc/cub3d.h"

int	handle_main_menu_keys(int keycode, t_cub3d *data)
{
	if (keycode == KEY_UP || keycode == KEY_W)
	{
		data->menu.menu_choice--;
		if (data->menu.menu_choice < 0)
			data->menu.menu_choice = 2;
		render_main_menu(data);
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		data->menu.menu_choice++;
		if (data->menu.menu_choice > 2)
			data->menu.menu_choice = 0;
		render_main_menu(data);
	}
	else if (keycode == KEY_RETURN || keycode == KEY_SPACE)
	{
		if (data->menu.menu_choice == 0)
		{
			data->status = DIFFICULTY_LEVEL;
			render_difficulty_menu(data);
		}
		else if (data->menu.menu_choice == 1)
		{
			data->status = CREDITS;
			render_credits(data);
		}
		else if (data->menu.menu_choice == 2)
			data->status = GAME;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	handle_difficulty_keys(int keycode, t_cub3d *data)
{
	if (keycode == KEY_UP || keycode == KEY_W)
	{
		data->menu.difficulty_choice--;
		if (data->menu.difficulty_choice < 0)
			data->menu.difficulty_choice = 2;
		render_difficulty_menu(data);
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		data->menu.difficulty_choice++;
		if (data->menu.difficulty_choice > 2)
			data->menu.difficulty_choice = 0;
		render_difficulty_menu(data);
	}
	else if (keycode == KEY_RETURN || keycode == KEY_SPACE)
	{
		data->status = MENU;
		render_main_menu(data);
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	menu_key_handler(int keycode, t_cub3d *data)
{
	if (data->status == MENU)
		return (handle_main_menu_keys(keycode, data));
	else if (data->status == DIFFICULTY_LEVEL)
		return (handle_difficulty_keys(keycode, data));
	else if (data->status == CREDITS)
	{
		if (keycode == KEY_ESC)
			exit(0);
		else if (keycode == KEY_BACKSPACE)
		{
			data->status = MENU;
			render_main_menu(data);
		}
		else if (keycode == KEY_LEFT || keycode == KEY_A)
		{
			if (data->menu.volume_level > 0)
			{
				data->menu.volume_level--;
				render_credits(data);
			}
		}
		else if (keycode == KEY_RIGHT || keycode == KEY_D)
		{
			if (data->menu.volume_level < 14)
			{
				data->menu.volume_level++;
				render_credits(data);
			}
		}
		return (0);
	}
	return (0);
}
