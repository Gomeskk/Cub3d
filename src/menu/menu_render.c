#include "../../inc/cub3d.h"

void	render_main_menu(t_cub3d *data)
{
	mlx_clear_window(data->mlx, data->window);
	
	if (data->menu.menu_choice == 0)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.start_normal.image, 0, 0);
	else if (data->menu.menu_choice == 1)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.start_hover.image, 0, 0);
	else if (data->menu.menu_choice == 2)
		mlx_put_image_to_window(data->mlx, data->window,
			data->menu.start_selected.image, 0, 0);
}

/* void	render_difficulty_menu(t_cub3d *data)
{
	mlx_clear_window(data->mlx, data->window);
	
	if difficulty_choice == 0:
	    mlx_put_image_to_window(data->mlx, data->window,
	        data->menu.diff_easy.image, 0, 0);
	else if difficulty_choice == 1:
	    mlx_put_image_to_window(data->mlx, data->window,
	        data->menu.diff_medium.image, 0, 0);
	else if difficulty_choice == 2:
	    mlx_put_image_to_window(data->mlx, data->window,
	        data->menu.diff_hard.image, 0, 0);
	
	Display navigation arrows at specific positions
	mlx_put_image_to_window(data->mlx, data->window,
	    data->menu.arrow_up.image, ARROW_X, ARROW_UP_Y);
	mlx_put_image_to_window(data->mlx, data->window,
	    data->menu.arrow_down.image, ARROW_X, ARROW_DOWN_Y);
} */
/* 
void	render_credits(t_cub3d *data)
{
	mlx_clear_window(data->mlx, data->window);
	mlx_put_image_to_window(data->mlx, data->window,
	    data->menu.credits_screen.image, 0, 0);
	mlx_string_put(data->mlx, data->window,
	    WIDTH/2, HEIGHT - 50, 0xFFFFFF, "Press ESC to return");
} */

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
