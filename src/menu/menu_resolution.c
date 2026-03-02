#include "../../inc/cub3d.h"

static int	close_window_handler(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static void	get_resolution_dimensions(int level, int *width, int *height)
{
	const int	widths[5] = {RES_0_WIDTH, RES_1_WIDTH, RES_2_WIDTH,
		RES_3_WIDTH, RES_4_WIDTH};
	const int	heights[5] = {RES_0_HEIGHT, RES_1_HEIGHT, RES_2_HEIGHT,
		RES_3_HEIGHT, RES_4_HEIGHT};

	*width = widths[level];
	*height = heights[level];
}

void	apply_resolution(t_cub3d *data, int new_level)
{
	int	new_width;
	int	new_height;

	get_resolution_dimensions(new_level, &new_width, &new_height);
	if (data->menu.screens.screen_buffer.image)
		mlx_destroy_image(data->mlx, data->menu.screens.screen_buffer.image);
	mlx_destroy_window(data->mlx, data->window);
	data->window = mlx_new_window(data->mlx, new_width, new_height,
			"Cub3D");
	if (!data->window)
		return ;
	data->current_width = new_width;
	data->current_height = new_height;
	data->menu.screens.screen_buffer.image = mlx_new_image(data->mlx, new_width,
			new_height);
	if (!data->menu.screens.screen_buffer.image)
		return ;
	data->menu.screens.screen_buffer.data = mlx_get_data_addr(
			data->menu.screens.screen_buffer.image,
			&data->menu.screens.screen_buffer.bpp,
			&data->menu.screens.screen_buffer.size_line,
			&data->menu.screens.screen_buffer.endian);
	data->menu.screens.screen_buffer.width = new_width;
	data->menu.screens.screen_buffer.height = new_height;
	data->menu.options.resolution_level = new_level;
	mlx_hook(data->window, 17, 0, close_window_handler, data);
	mlx_hook(data->window, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->window, 3, 1L << 1, key_release_handler, data);
}
