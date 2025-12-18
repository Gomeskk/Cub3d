#include "../../inc/cub3d.h"

int	init_start_game_images(t_cub3d *data)
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

int	init_difficulty_images(t_cub3d *data)
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

int	init_volume_images(t_cub3d *data)
{
	const char	*paths[15] = {
		"Png_images/VolumePNG/Volume Cub3D (-7).xpm",
		"Png_images/VolumePNG/Volume Cub3D (-6).xpm",
		"Png_images/VolumePNG/Volume Cub3D (-5).xpm",
		"Png_images/VolumePNG/Volume Cub3D (-4).xpm",
		"Png_images/VolumePNG/Volume Cub3D (-3).xpm",
		"Png_images/VolumePNG/Volume Cub3D (-2).xpm",
		"Png_images/VolumePNG/Volume Cub3D (-1).xpm",
		"Png_images/VolumePNG/Volume Cub3D.xpm",
		"Png_images/VolumePNG/Volume Cub3D (+1).xpm",
		"Png_images/VolumePNG/Volume Cub3D (+2).xpm",
		"Png_images/VolumePNG/Volume Cub3D (+3).xpm",
		"Png_images/VolumePNG/Volume Cub3D (+4).xpm",
		"Png_images/VolumePNG/Volume Cub3D (+5).xpm",
		"Png_images/VolumePNG/Volume Cub3D (+6).xpm",
		"Png_images/VolumePNG/Volume Cub3D (+7).xpm"
	};
	int	i;

	i = 0;
	while (i < 15)
	{
		data->menu.volume[i].image = mlx_xpm_file_to_image(data->mlx,
			(char *)paths[i], &data->menu.volume[i].width,
			&data->menu.volume[i].height);
		if (!data->menu.volume[i].image)
			return (-1);
		i++;
	}
	return (0);
}

int	init_sensibility_images(t_cub3d *data)
{
	const char	*paths[5] = {
		"Png_images/SensibilityPNG/Sensibility Cub3D (0).xpm",
		"Png_images/SensibilityPNG/Sensibility Cub3D (0.5).xpm",
		"Png_images/SensibilityPNG/Sensibility Cub3D (1).xpm",
		"Png_images/SensibilityPNG/Sensibility Cub3D (1.5).xpm",
		"Png_images/SensibilityPNG/Sensibility Cub3D (2).xpm"
	};
	int	i;

	i = 0;
	while (i < 5)
	{
		data->menu.sensibility[i].image = mlx_xpm_file_to_image(data->mlx,
			(char *)paths[i], &data->menu.sensibility[i].width,
			&data->menu.sensibility[i].height);
		if (!data->menu.sensibility[i].image)
			return (-1);
		i++;
	}
	return (0);
}

int	init_options_images(t_cub3d *data)
{
	data->menu.options_screen.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Options/Options Cub3D00.xpm",
		&data->menu.options_screen.width,
		&data->menu.options_screen.height);
	if (!data->menu.options_screen.image)
		return (-1);
	if (init_volume_images(data) == -1)
		return (-1);
	if (init_sensibility_images(data) == -1)
		return (-1);
	return (0);
}
