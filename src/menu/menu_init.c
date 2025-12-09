#include "../../inc/cub3d.h"

static int	init_start_game_images(t_cub3d *data)
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

static int	init_difficulty_images(t_cub3d *data)
{
	data->menu.diff_easy.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Difficulty/Difficulty  Cub3D_00.xpm",
		&data->menu.diff_easy.width,
		&data->menu.diff_easy.height);
	if (!data->menu.diff_easy.image)
		return (-1);
	data->menu.diff_medium.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Difficulty/Difficulty  Cub3D_01.xpm",
		&data->menu.diff_medium.width,
		&data->menu.diff_medium.height);
	if (!data->menu.diff_medium.image)
		return (-1);
	data->menu.diff_hard.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Difficulty/Difficulty Cub3D_02.xpm",
		&data->menu.diff_hard.width,
		&data->menu.diff_hard.height);
	if (!data->menu.diff_hard.image)
		return (-1);
	return (0);
}

static int	init_options_images(t_cub3d *data)
{
	data->menu.sensibility[0].image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Options/Options Cub3D00.xpm",
		&data->menu.sensibility[0].width,
		&data->menu.sensibility[0].height);
	if (!data->menu.sensibility[0].image)
		return (-1);
	return (0);
}

int	init_menu_images(t_cub3d *data)
{
	if (init_start_game_images(data) == -1)
		return (-1);
	if (init_difficulty_images(data) == -1)
		return (-1);
	if (init_options_images(data) == -1)
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
	if (data->menu.diff_easy.image)
		mlx_destroy_image(data->mlx, data->menu.diff_easy.image);
	if (data->menu.diff_medium.image)
		mlx_destroy_image(data->mlx, data->menu.diff_medium.image);
	if (data->menu.diff_hard.image)
		mlx_destroy_image(data->mlx, data->menu.diff_hard.image);
	if (data->menu.sensibility[0].image)
		mlx_destroy_image(data->mlx, data->menu.sensibility[0].image);
}
