#include "../../inc/cub3d.h"

/*
** Navigate through main menu options (cycle up/down)
** Updates menu choice and re-renders main menu
*/
static void	navigate_menu(t_cub3d *data, int direction)
{
	data->menu.menu_choice += direction;
	if (data->menu.menu_choice < MENU_START)
		data->menu.menu_choice = MENU_CREDITS;
	else if (data->menu.menu_choice > MENU_CREDITS)
		data->menu.menu_choice = MENU_START;
	render_main_menu(data);
}

/*
** Select current menu option
** Start: go to difficulty, Options: go to options menu, Credits: show credits
*/
static void	select_menu_option(t_cub3d *data)
{
	if (data->menu.menu_choice == MENU_START)
	{
		data->status = DIFFICULTY_SCREEN;
		render_difficulty_menu(data);
	}
	else if (data->menu.menu_choice == MENU_OPTIONS)
	{
		data->status = OPTIONS_SCREEN;
		render_options_menu(data);
	}
	else if (data->menu.menu_choice == MENU_CREDITS)
	{
		data->status = CREDITS_SCREEN;
		render_credits_screen(data);
	}
}

/*
** Handle key inputs on main menu screen
** Up/Down: navigate menu, Enter: select option, Escape: exit game
*/
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

/*
** Change difficulty selection (cycle through easy/medium/hard)
** Updates difficulty choice and re-renders difficulty menu
*/
static void	change_difficulty(t_cub3d *data, int direction)
{
	data->menu.difficulty_choice += direction;
	if (data->menu.difficulty_choice > DIFF_HARD)
		data->menu.difficulty_choice = DIFF_EASY;
	else if (data->menu.difficulty_choice < DIFF_EASY)
		data->menu.difficulty_choice = DIFF_HARD;
	render_difficulty_menu(data);
}

/*
** Handle key inputs on difficulty selection screen
** Up/Down: cycle difficulty, Enter: go to skin selection, Escape: back to main menu
*/
int	handle_difficulty_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
		change_difficulty(data, 1);
	else if (keycode == XK_Down || keycode == XK_s)
		change_difficulty(data, -1);
	else if (keycode == XK_Return)
	{
		data->status = SKIN_SELECT;
		render_skin_select(data);
	}
	else if (keycode == XK_Escape)
	{
		data->menu.menu_choice = MENU_START;
		data->status = MAIN_MENU_SCREEN;
		render_main_menu(data);
	}
	return (0);
}

/*
** Change skin selection (cycle through available skins)
** Updates skin choice, tracks arrow direction, and re-renders skin selection screen
*/
static void	change_skin(t_cub3d *data, int direction)
{
	data->menu.skin_choice += direction;
	// Assuming we have multiple skins, adjust range as needed
	// For now, cycle between 0-2 (3 skins)
	if (data->menu.skin_choice > 2)
		data->menu.skin_choice = 0;
	else if (data->menu.skin_choice < 0)
		data->menu.skin_choice = 2;
	// Track which arrow was pressed: -1 for left, 1 for right
	data->menu.last_skin_arrow_direction = direction;
	render_skin_select(data);
}

/*
** Handle key inputs on skin selection screen
** Left/Right: cycle skins, Enter: start game, Escape: back to difficulty
*/
int	handle_skin_select_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Left || keycode == XK_a)
		change_skin(data, -1);
	else if (keycode == XK_Right || keycode == XK_d)
		change_skin(data, 1);
	else if (keycode == XK_Return)
		data->status = GAME;
	else if (keycode == XK_Escape)
	{
		data->status = DIFFICULTY_SCREEN;
		render_difficulty_menu(data);
	}
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
