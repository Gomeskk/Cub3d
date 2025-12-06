#include "../../inc/cub3d.h"

int	handle_main_menu_keys(int keycode, t_cub3d *data)
{
/* 	if keycode == KEY_UP or keycode == KEY_W:
	    data->menu_choice--;
	    if data->menu_choice < 0:
	        data->menu_choice = 2; // Wrap to last option
	else if keycode == KEY_DOWN or keycode == KEY_S:
	    data->menu_choice++;
	    if data->menu_choice > 2:
	        data->menu_choice = 0; // Wrap to first option
	else if keycode == KEY_RETURN or keycode == KEY_SPACE:
	    switch data->menu_choice:
	        case 0: // Start Game
	            data->status = GAME;
	            // Initialize game if needed
	            break;
	        case 1: // Difficulty
	            data->status = DIFFICULTY_LEVEL;
	            break;
	        case 2: // Credits
	            data->status = CREDITS;
	            break;
	else if keycode == KEY_ESC:
	    cleanup_and_exit(data);
	return 0; */
}

int	handle_difficulty_keys(int keycode, t_cub3d *data)
{	
/*     if keycode == KEY_LEFT or keycode == KEY_A:
	    data->difficulty_choice--;
	    if data->difficulty_choice < 0:
	        data->difficulty_choice = 2;
	else if keycode == KEY_RIGHT or keycode == KEY_D:
	    data->difficulty_choice++;
	    if data->difficulty_choice > 2:
	        data->difficulty_choice = 0;
	else if keycode == KEY_RETURN or keycode == KEY_SPACE:
	    // Apply difficulty settings
	    apply_difficulty_settings(data);
	    data->status = MENU;
	else if keycode == KEY_ESC:
	    data->status = MENU; // Return without saving
	return 0; */
}

int	menu_key_handler(int keycode, t_cub3d *data)
{
/* 	switch data->status:
	    case MENU:
	        return handle_main_menu_keys(keycode, data);
	    case DIFFICULTY_LEVEL:
	        return handle_difficulty_keys(keycode, data);
	    case CREDITS:
	        if keycode == KEY_ESC:
	            data->status = MENU;
	        return 0;
	    case GAME:
	        // Call your game key handler
	        return handle_game_keys(keycode, data);
	return 0; */
}
