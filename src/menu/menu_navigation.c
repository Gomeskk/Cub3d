#include "../../inc/cub3d.h"
#include <stdio.h>

int	handle_main_menu_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
	{
		data->menu.menu_choice--;
		if (data->menu.menu_choice < MENU_START)
			data->menu.menu_choice = MENU_EXIT;
		render_main_menu(data);
	}
	else if (keycode == XK_Down || keycode == XK_s)
	{
		data->menu.menu_choice++;
		if (data->menu.menu_choice > MENU_EXIT)
			data->menu.menu_choice = MENU_START;
		render_main_menu(data);
	}
	else if (keycode == XK_Return)
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
	else if (keycode == XK_Escape)
		exit(0);
	return (0);
}

int	handle_difficulty_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
	{
		data->menu.difficulty_choice--;
		if (data->menu.difficulty_choice < DIFF_EASY)
			data->menu.difficulty_choice = DIFF_HARD;
		render_difficulty_menu(data);
	}
	else if (keycode == XK_Down || keycode == XK_s)
	{
		data->menu.difficulty_choice++;
		if (data->menu.difficulty_choice > DIFF_HARD)
			data->menu.difficulty_choice = DIFF_EASY;
		render_difficulty_menu(data);
	}
	else if (keycode == XK_Return)
	{
		printf("Starting game with difficulty: %d\n", data->menu.difficulty_choice);
		// TODO: Start actual game here
		// For now, return to main menu
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		render_main_menu(data);
	}
	else if (keycode == XK_Escape)
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
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		data->menu.options_section = 0;
		render_main_menu(data);
	}
	else if (keycode == XK_Tab || keycode == KEY_TAB)
	{
		data->menu.options_section = (data->menu.options_section + 1) % 3;
		printf("DEBUG: TAB pressed - section now: %d (0=Sound, 1=Resolution, 2=Sensibility)\n", 
			data->menu.options_section);
		printf("       Current values: volume=%d, resolution=%d, sensibility=%d\n",
			data->menu.volume_level, data->menu.resolution_level, data->menu.sensibility_level);
		render_credits(data);
	}
	else if (keycode == XK_Left || keycode == XK_a)
	{
		if (data->menu.options_section == 0 && data->menu.volume_level > 0)
		{
			data->menu.volume_level--;
			printf("DEBUG: Volume decreased to %d\n", data->menu.volume_level);
			render_credits(data);
		}
		else if (data->menu.options_section == 2 && data->menu.sensibility_level > 0)
		{
			data->menu.sensibility_level--;
			render_credits(data);
		}
	}
	else if (keycode == XK_Right || keycode == XK_d)
	{
		if (data->menu.options_section == 0 && data->menu.volume_level < 14)
		{
			data->menu.volume_level++;
			printf("DEBUG: Volume increased to %d\n", data->menu.volume_level);
			render_credits(data);
		}
		else if (data->menu.options_section == 2 && data->menu.sensibility_level < 4)
		{
			data->menu.sensibility_level++;
			render_credits(data);
		}
	}
	else if (keycode == XK_Up || keycode == XK_w)
	{
		if (data->menu.options_section == 1 && data->menu.resolution_level < 2)
		{
			data->menu.resolution_level++;
			render_credits(data);
		}
	}
	else if (keycode == XK_Down || keycode == XK_s)
	{
		if (data->menu.options_section == 1 && data->menu.resolution_level > 0)
		{
			data->menu.resolution_level--;
			render_credits(data);
		}
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
		return (handle_credits_keys(keycode, data));
	return (0);
}
