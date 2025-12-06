#include "../../inc/cub3d.h"

int	init_menu_images(t_cub3d *data)
{
/* 	Allocate menu structure
	data->menu = malloc(sizeof(t_menu));
	
	Load main menu images (StartGame folder) - use mlx_xpm_file_to_image directly
	Example:
	data->menu.start_normal.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/StartGame/Cub3D0.xpm",
		&data->menu.start_normal.width,
		&data->menu.start_normal.height);
	if (!data->menu.start_normal.image)
		return (-1); // Handle error
        
	Repeat for all images:
	data->menu.start_hover = mlx_xpm_file_to_image(...)
	data->menu.start_selected = mlx_xpm_file_to_image(...)
	data->menu.diff_easy = mlx_xpm_file_to_image(...)
	data->menu.diff_medium = mlx_xpm_file_to_image(...)
	data->menu.diff_hard = mlx_xpm_file_to_image(...)
	data->menu.arrow_up = mlx_xpm_file_to_image(...)
	data->menu.arrow_down = mlx_xpm_file_to_image(...)	
	data->menu.sensibility[0] = mlx_xpm_file_to_image(...) // 0.0
	data->menu.sensibility[1] = mlx_xpm_file_to_image(...) // 0.5
	data->menu.sensibility[2] = mlx_xpm_file_to_image(...) // 1.5
	data->menu.sensibility[3] = mlx_xpm_file_to_image(...) // 2.0
	data->menu.credits_screen = mlx_xpm_file_to_image(...)
	
	Check for loading errors - if any image failed: cleanup and return error
	return (0); */
}

void	init_menu_state(t_cub3d *data)
{
/* 	data->menu_choice = 0;
	data->difficulty_choice = 1;  // Medium difficulty default
	data->sensibility_level = 0;   // Normal mouse sensibility
	data->status = MENU;
	data->fps_timer = 0.0; */
}

void	cleanup_menu(t_cub3d *data)
{
/* 	if data->menu exists:
	    Destroy all loaded images
	    mlx_destroy_image(data->mlx, data->menu.start_normal)
	    mlx_destroy_image(data->mlx, data->menu.start_hover)
	    ... destroy all other images
	    free(data->menu)
	    data->menu = NULL */
}
