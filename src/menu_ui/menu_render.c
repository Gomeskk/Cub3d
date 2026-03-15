#include "../../inc/cub3d.h"

/*
** Calculate scale factor for current resolution
** Scales menu images to maintain proper aspect ratio on different resolutions
*/
static float	get_scale(t_cub3d *data)
{
	return ((float)data->current_width / (float)RES_4_WIDTH);
}

/*
** Render main menu screen
** Shows start/options/exit with appropriate highlighting based on selection
*/
void	render_main_menu(t_cub3d *data)
{
	t_menu_img	*img;
	float		scale;

	scale = get_scale(data);
	mlx_clear_window(data->mlx, data->window);
	if (data->menu.menu_choice == MENU_START)
		img = &data->menu.screens.start_normal;
	else if (data->menu.menu_choice == MENU_OPTIONS)
		img = &data->menu.screens.start_hover;
	else
		img = &data->menu.screens.start_selected;
	put_img_to_img_scaled(&data->menu.screens.screen_buffer, *img, 0, 0, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screens.screen_buffer.image, 0, 0);
}

/*
** Render difficulty selection screen
** Shows easy/medium/hard difficulty options with current selection highlighted
*/
void	render_difficulty_menu(t_cub3d *data)
{
	t_menu_img	*img;
	float		scale;

	scale = get_scale(data);
	mlx_clear_window(data->mlx, data->window);
	if (data->menu.difficulty_choice == DIFF_EASY)
		img = &data->menu.difficulty.easy;
	else if (data->menu.difficulty_choice == DIFF_MEDIUM)
		img = &data->menu.difficulty.medium;
	else
		img = &data->menu.difficulty.hard;
	put_img_to_img_scaled(&data->menu.screens.screen_buffer, *img, 0, 0, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screens.screen_buffer.image, 0, 0);
}

/*
** Render skin selection screen
** Shows base skin image with arrow overlay (left or right) on top
*/
void	render_skin_select(t_cub3d *data)
{
	float	scale;

	scale = get_scale(data);
	// Always render base skin selection screen first
	put_img_to_img_scaled(&data->menu.screens.screen_buffer,
		data->menu.screens.skin_select, 0, 0, scale);
	// Overlay arrow on top: left arrow or right arrow
	if (data->menu.last_skin_arrow_direction == -1)
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.screens.arrow_left, 0, 0, scale);
	else
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.screens.arrow_right, 0, 0, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screens.screen_buffer.image, 0, 0);
}

/*
** Render volume and sensibility level indicators
** Positions scaled images at specific coordinates on screen
*/
void	render_volume_sensibility(t_cub3d *data, float scale)
{
	int	vol_x;
	int	vol_y;
	int	sens_x;
	int	sens_y;

	vol_x = (int)(VOLUME_IMG_X * scale);
	vol_y = (int)(VOLUME_IMG_Y * scale);
	sens_x = (int)(SENSIBILITY_IMG_X * scale);
	sens_y = (int)(SENSIBILITY_IMG_Y * scale);
	put_img_to_img_scaled(&data->menu.screens.screen_buffer,
		data->menu.options_imgs.volume[data->menu.options.volume_level],
		vol_x, vol_y, scale);
	put_img_to_img_scaled(&data->menu.screens.screen_buffer,
		data->menu.options_imgs.sensibility[data->menu.options.sensibility_level],
		sens_x, sens_y, scale);
}

/*
** Render credits screen
** Shows game credits with instructions to start or go back
*/
void	render_credits_screen(t_cub3d *data)
{
	t_menu_img	*img;
	float		scale;

	scale = (float)data->current_width / (float)RES_4_WIDTH;
	mlx_clear_window(data->mlx, data->window);
	img = &data->menu.screens.credits_screen;
	put_img_to_img_scaled(&data->menu.screens.screen_buffer, *img, 0, 0, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screens.screen_buffer.image, 0, 0);
}

