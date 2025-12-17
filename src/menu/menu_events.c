#include "../../inc/cub3d.h"

int	handle_main_menu_keys(int keycode, t_cub3d *data)
{
	if (keycode == KEY_UP || keycode == KEY_W)
	{
		data->menu.menu_choice--;
		if (data->menu.menu_choice < MENU_START)
			data->menu.menu_choice = MENU_EXIT;
		render_main_menu(data);
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		data->menu.menu_choice++;
		if (data->menu.menu_choice > MENU_EXIT)
			data->menu.menu_choice = MENU_START;
		render_main_menu(data);
	}
	else if (keycode == KEY_RETURN || keycode == KEY_SPACE)
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
		else if (data->menu.menu_choice == MENU_EXIT)
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
		if (data->menu.difficulty_choice < DIFF_EASY)
			data->menu.difficulty_choice = DIFF_HARD;
		render_difficulty_menu(data);
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		data->menu.difficulty_choice++;
		if (data->menu.difficulty_choice > DIFF_HARD)
			data->menu.difficulty_choice = DIFF_EASY;
		render_difficulty_menu(data);
	}
	else if (keycode == KEY_RETURN)
	{
		printf("Starting game with difficulty: %d\n", data->menu.difficulty_choice);
		// TODO: Start actual game here
		// For now, return to main menu
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		render_main_menu(data);
	}
	else if (keycode == KEY_ESC)
	{
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		render_main_menu(data);
	}
	return (0);
}

int	menu_key_handler(int keycode, t_cub3d *data)
{
	if (data->status == MAIN_MENU_SCREEN)
		return (handle_main_menu_keys(keycode, data));
	else if (data->status == DIFFICULTY_SCREEN)
		return (handle_difficulty_keys(keycode, data));
	else if (data->status == CREDITS)
	{
		if (keycode == KEY_ESC)
		{
			data->menu.menu_choice = MENU_START;
			data->status = MAIN_MENU_SCREEN;
			data->menu.options_section = 0;
			render_main_menu(data);
		}
		else if (keycode == KEY_UP || keycode == KEY_W)
		{
			if (data->menu.options_section > 0)
				data->menu.options_section--;
		}
		else if (keycode == KEY_DOWN || keycode == KEY_S)
		{
			if (data->menu.options_section < 1)
				data->menu.options_section++;
		}
		else if (keycode == KEY_LEFT || keycode == KEY_A)
		{
			if (data->menu.options_section == 0)
			{
				if (data->menu.volume_level > 0)
				{
					data->menu.volume_level--;
					render_credits(data);
				}
			}
			else if (data->menu.options_section == 1)
			{
				if (data->menu.sensibility_level > 0)
				{
					data->menu.sensibility_level--;
					render_credits(data);
				}
			}
		}
		else if (keycode == KEY_RIGHT || keycode == KEY_D)
		{
			if (data->menu.options_section == 0)
			{
				if (data->menu.volume_level < 14)
				{
					data->menu.volume_level++;
					render_credits(data);
				}
			}
			else if (data->menu.options_section == 1)
			{
				if (data->menu.sensibility_level < 4)
				{
					data->menu.sensibility_level++;
					render_credits(data);
				}
			}
		}
		return (0);
	}
	return (0);
}
