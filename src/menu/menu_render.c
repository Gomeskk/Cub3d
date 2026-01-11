#include "../../inc/cub3d.h"
#include <stdio.h>

void	render_main_menu(t_cub3d *data)
{
	mlx_clear_window(data->mlx, data->window);
	
	if (data->menu.menu_choice == MENU_START)
	{
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.start_normal.image, 0, 0);
	}
	else if (data->menu.menu_choice == MENU_OPTIONS)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.start_hover.image, 0, 0);
	else if (data->menu.menu_choice == MENU_CREDITS)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.start_selected.image, 0, 0);
}

void	render_difficulty_menu(t_cub3d *data)
{
	mlx_clear_window(data->mlx, data->window);
	
	if (data->menu.difficulty_choice == DIFF_EASY)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.diff_easy.image, 0, 0);
	else if (data->menu.difficulty_choice == DIFF_MEDIUM)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.diff_medium.image, 0, 0);
	else if (data->menu.difficulty_choice == DIFF_HARD)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.diff_hard.image, 0, 0);
}

void	render_credits(t_cub3d *data)
{
	put_img_to_img(&data->menu.screen_buffer, data->menu.options_screen, 0, 0);
	
	// Always render all current values
	put_img_to_img(&data->menu.screen_buffer, data->menu.volume[data->menu.volume_level], 203, 392);
	put_img_to_img(&data->menu.screen_buffer, data->menu.sensibility[data->menu.sensibility_level], 197, 876);
	
	// Then overlay the highlighted tab on top
	if (data->menu.options_section == 0)
		put_img_to_img(&data->menu.screen_buffer, data->menu.tab_sound, 0, 0);
	else if (data->menu.options_section == 1)
		put_img_to_img(&data->menu.screen_buffer, data->menu.tab_resolution, 0, 0);
	else if (data->menu.options_section == 2)
		put_img_to_img(&data->menu.screen_buffer, data->menu.tab_sensibility, 0, 0);
	
	mlx_put_image_to_window(data->mlx, data->window, data->menu.screen_buffer.image, 0, 0);
}

/* int	render_game_handler(t_cub3d *data)
{
	static double time = 0;
	time += get_delta_time(); // You need to implement this
	if time >= 1.0 / FPS:
	    switch data->status:
	        case MENU:
	            render_main_menu(data);
	            break;
	        case DIFFICULTY_LEVEL:
	            render_difficulty_menu(data);
	            break;
	        case CREDITS:
	            render_credits(data);
	            break;
	        case GAME:
	            render_gameplay(data); // Your actual game rendering
	            break;
	    time = 0;
	return 0;
} */