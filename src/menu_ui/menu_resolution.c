#include "../../inc/cub3d.h"

/*
** Get resolution dimensions from level index
** LOOKUP TABLE: Uses const arrays to map level (0-4) to actual dimensions
** This is faster than switch/if-else and keeps resolution data centralized
** Levels: 0=960x540, 1=1280x720, 2=1600x900, 3=1920x1080, 4=custom
*/
static void	get_resolution_dimensions(int level, int *width, int *height)
{
	const int	widths[5] = {RES_0_WIDTH, RES_1_WIDTH, RES_2_WIDTH,
		RES_3_WIDTH, RES_4_WIDTH};
	const int	heights[5] = {RES_0_HEIGHT, RES_1_HEIGHT, RES_2_HEIGHT,
		RES_3_HEIGHT, RES_4_HEIGHT};

	*width = widths[level];
	*height = heights[level];
}

// Destroy old window and images to free memory before creating new ones
static void	destroy_old_resources(t_cub3d *data)
{
	// Destroy menu compositing buffer image
	if (data->menu.screens.screen_buffer.image)
		mlx_destroy_image(data->mlx, data->menu.screens.screen_buffer.image);
	// Destroy game rendering image
	if (data->img.image)
		mlx_destroy_image(data->mlx, data->img.image);
	// Now safe to destroy window after images are freed
	mlx_destroy_window(data->mlx, data->window);
}

// Aply new resolution - complete window/image recreation
void	apply_resolution(t_cub3d *data, int new_level)
{
	int	new_width;
	int	new_height;

	// Get dimensions for this resolution level
	get_resolution_dimensions(new_level, &new_width, &new_height);
	// Clean up old window and images
	destroy_old_resources(data);
	// Create new window with new size
	if (!create_new_window(data, new_width, new_height))
		return ;
	// Create menu compositing buffer
	if (!create_menu_buffer(data, new_width, new_height))
		return ;
	// Create game rendering image
	if (!create_game_image(data, new_width, new_height))
		return ;
	// Update tracking variables
	update_resolution_settings(data, new_level, new_width, new_height);
	// Reattach event hooks to new window (MLX requirement)
	reattach_hooks(data);
}
