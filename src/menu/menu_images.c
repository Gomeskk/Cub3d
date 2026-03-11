#include "../../inc/cub3d.h"

int	load_xpm_with_data(void *mlx, t_menu_img *img, char *path)
{
	img->image = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->image)
		return (-1);
	img->data = mlx_get_data_addr(img->image, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
		return (-1);
	return (0);
}

int	init_start_game_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.screens.start_normal,
			"Png_images/StartGame/StartGame.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.start_hover,
			"Png_images/StartGame/Options.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.start_selected,
			"Png_images/StartGame/Credits.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.credits_screen,
			"Png_images/Credits/Credits.xpm") == -1)
		return (-1);
	return (0);
}

int	init_difficulty_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.difficulty.easy,
			"Png_images/Difficulty/Easy.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.difficulty.medium,
			"Png_images/Difficulty/Medium.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.difficulty.hard,
			"Png_images/Difficulty/Hard.xpm") == -1)
		return (-1);
	return (0);
}

int	init_skin_select_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.screens.skin_select,
			"Png_images/SkinSelection/SkinSelect.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_left,
			"Png_images/SkinSelection/ArrowLeft.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_right,
			"Png_images/SkinSelection/ArrowRight.xpm") == -1)
		return (-1);
	return (0);
}

static int	init_options_base_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.screens.options_screen,
			"Png_images/Options/OptionsMenu.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_up,
			"Png_images/Arrow/UP(PINK).xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_down,
			"Png_images/Arrow/DOWN(PINK).xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.tab_sound,
			"Png_images/TabChoices/TabSound.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.tab_resolution,
			"Png_images/TabChoices/TabResolution.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.tab_sensibility,
			"Png_images/TabChoices/TabSensibility.xpm") == -1)
		return (-1);
	return (0);
}

static int	init_options_resolution_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.resolution_approve,
			"Png_images/ScreenSize/ResolutionAprove.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.resolution_decline,
			"Png_images/ScreenSize/ResolutionDeclined.xpm") == -1)
		return (-1);
	if (init_volume_images(data) == -1)
		return (-1);
	if (init_sensibility_images(data) == -1)
		return (-1);
	if (init_resolution_images(data) == -1)
		return (-1);
	return (0);
}

int	init_options_images(t_cub3d *data)
{
	if (init_options_base_images(data) == -1)
		return (-1);
	if (init_options_resolution_images(data) == -1)
		return (-1);
	return (0);
}
