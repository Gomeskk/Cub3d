#include "../../inc/cub3d.h"

int	init_menu_images(t_cub3d *data)
{
	data->menu.start_normal.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/StartGame/Cub3D0.xpm",
		&data->menu.start_normal.width,
		&data->menu.start_normal.height);
	if (!data->menu.start_normal.image)
		return (-1);
	data->menu.start_hover.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/StartGame/Cub3D01.xpm",
		&data->menu.start_hover.width,
		&data->menu.start_hover.height);
	if (!data->menu.start_hover.image)
		return (-1);
	data->menu.start_selected.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/StartGame/Cub3D02.xpm",
		&data->menu.start_selected.width,
		&data->menu.start_selected.height);
	if (!data->menu.start_selected.image)
		return (-1);
	return (0);
}

void	init_menu_state(t_cub3d *data)
{
	data->menu.menu_choice = 0;
	data->menu.difficulty_choice = 1;
	data->menu.sensibility_level = 0;
	data->status = MENU;
}

void	cleanup_menu(t_cub3d *data)
{
	if (data->menu.start_normal.image)
		mlx_destroy_image(data->mlx, data->menu.start_normal.image);
	if (data->menu.start_hover.image)
		mlx_destroy_image(data->mlx, data->menu.start_hover.image);
	if (data->menu.start_selected.image)
		mlx_destroy_image(data->mlx, data->menu.start_selected.image);
}
