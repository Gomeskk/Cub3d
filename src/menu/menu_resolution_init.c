#include "../../inc/cub3d.h"

/*
** Create new window with specified dimensions
** Returns 1 on success, 0 on failure
** Also updates current_width and current_height tracking variables
*/
int	create_new_window(t_cub3d *data, int width, int height)
{
	// Create new MLX window
	data->window = mlx_new_window(data->mlx, width, height, "Cub3D");
	if (!data->window)
		return (0);
	// Force X11 to process all pending requests
	mlx_do_sync(data->mlx);
	
	// Update global dimension tracking
	data->current_width = width;
	data->current_height = height;
	return (1);
}

/*
** Create menu screen buffer for new resolution
** DOUBLE BUFFERING: All menu elements are drawn to this buffer first,
** then the complete buffer is displayed to window (prevents flickering)
** Returns 1 on success, 0 on failure
*/
int	create_menu_buffer(t_cub3d *data, int width, int height)
{
	// Create new image buffer
	data->menu.screens.screen_buffer.image = mlx_new_image(data->mlx,
			width, height);
	if (!data->menu.screens.screen_buffer.image)
		return (0);
	// Get buffer data address for direct pixel manipulation
	data->menu.screens.screen_buffer.data = mlx_get_data_addr(
			data->menu.screens.screen_buffer.image,
			&data->menu.screens.screen_buffer.bpp,
			&data->menu.screens.screen_buffer.size_line,
			&data->menu.screens.screen_buffer.endian);
	// Store dimensions in buffer struct
	data->menu.screens.screen_buffer.width = width;
	data->menu.screens.screen_buffer.height = height;
	return (1);
}

/*
** Create game rendering image for new resolution
** This is where the 3D raycasting output is drawn
** Returns 1 on success, 0 on failure
*/
int	create_game_image(t_cub3d *data, int width, int height)
{
	// Create new rendering image
	data->img.image = mlx_new_image(data->mlx, width, height);
	if (!data->img.image)
		return (0);
	// Get image data address for direct pixel writing
	data->img.data = mlx_get_data_addr(data->img.image,
			&data->img.bpp, &data->img.size_line, &data->img.type);
	// Store dimensions
	data->img.width = width;
	data->img.height = height;
	// Reallocate z_buffer for new resolution width
	free(data->z_buffer);
	data->z_buffer = malloc(sizeof(double) * width);
	return (1);
}

// Update resolution tracking and mouse center position
void	update_resolution_settings(t_cub3d *data, int level, int width, int height)
{
	// Store current resolution level (for menu display)
	data->menu.options.resolution_level = level;
	// Recalculate screen center for mouse rotation reference point
	data->mouse.cx = width / 2;
	data->mouse.cy = height / 2;
}
