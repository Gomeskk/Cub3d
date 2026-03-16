#include "../../inc/cub3d.h"

int	load_image_array(void *mlx, t_menu_img *imgs,
		const char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (load_xpm_with_data(mlx, &imgs[i], (char *)paths[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_volume_images(t_cub3d *data)
{
	const char	*paths[15] = {"Png_images/Volume/(-7).xpm",
		"Png_images/Volume/(-6).xpm", "Png_images/Volume/(-5).xpm",
		"Png_images/Volume/(-4).xpm", "Png_images/Volume/(-3).xpm",
		"Png_images/Volume/(-2).xpm", "Png_images/Volume/(-1).xpm",
		"Png_images/Volume/(0).xpm", "Png_images/Volume/(+1).xpm",
		"Png_images/Volume/(+2).xpm", "Png_images/Volume/(+3).xpm",
		"Png_images/Volume/(+4).xpm", "Png_images/Volume/(+5).xpm",
		"Png_images/Volume/(+6).xpm", "Png_images/Volume/(+7).xpm"};

	return (load_image_array(data->mlx, data->menu.options_imgs.volume, paths,
			VOLUME_COUNT));
}

int	init_sensibility_images(t_cub3d *data)
{
	const char	*paths[5] = {"Png_images/Sensibility/(0).xpm",
		"Png_images/Sensibility/(0.5).xpm", "Png_images/Sensibility/(1).xpm",
		"Png_images/Sensibility/(1.5).xpm", "Png_images/Sensibility/(2).xpm"};

	return (load_image_array(data->mlx, data->menu.options_imgs.sensibility,
			paths, SENSIBILITY_COUNT));
}

int	init_resolution_images(t_cub3d *data)
{
	const char	*paths[5] = {"Png_images/ScreenSize/960×540.xpm",
		"Png_images/ScreenSize/1280×720.xpm",
		"Png_images/ScreenSize/1440x810.xpm",
		"Png_images/ScreenSize/1600x900.xpm",
		"Png_images/ScreenSize/1920x1080.xpm"};

	return (load_image_array(data->mlx, data->menu.options_imgs.resolution,
			paths, RESOLUTION_COUNT));
}
