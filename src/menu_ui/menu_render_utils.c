#include "../../inc/cub3d.h"

/*
** Render resolution confirmation dialog
** Shows approve/decline options based on user choice
*/
static void	render_resolution_confirm(t_cub3d *data, float scale)
{
	if (data->menu.options.resolution_confirm_choice == 0)
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.options_imgs.resolution_decline, 0, 0, scale);
	else
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.options_imgs.resolution_approve, 0, 0, scale);
}

/*
** Render resolution section overlay
** Shows tab highlight, confirmation dialog, or arrow indicators
*/
static void	render_resolution_section(t_cub3d *data, float scale)
{
	put_img_to_img_scaled(&data->menu.screens.screen_buffer,
		data->menu.options_imgs.tab_resolution, 0, 0, scale);
	if (data->menu.options.resolution_confirm_active)
		render_resolution_confirm(data, scale);
	else if (data->menu.options.last_arrow_direction == -1)
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.screens.arrow_down, 0, 0, scale);
	else
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.screens.arrow_up, 0, 0, scale);
}

/*
** Render options section overlay (tab highlight)
** Shows which section is currently selected: sound/resolution/sensibility
*/
static void	render_options_overlay(t_cub3d *data, float scale)
{
	if (data->menu.options.section == SECTION_SOUND)
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.options_imgs.tab_sound, 0, 0, scale);
	else if (data->menu.options.section == SECTION_RESOLUTION)
		render_resolution_section(data, scale);
	else if (data->menu.options.section == SECTION_SENSIBILITY)
		put_img_to_img_scaled(&data->menu.screens.screen_buffer,
			data->menu.options_imgs.tab_sensibility, 0, 0, scale);
}

/*
** Render complete options menu screen
** Composites base screen, volume/sensibility, resolution, and overlay
*/
void	render_options_menu(t_cub3d *data)
{
	float	scale;
	int		res_level;

	scale = (float)data->current_width / (float)RES_4_WIDTH;
	res_level = data->menu.options.pending_resolution_level;
	put_img_to_img_scaled(&data->menu.screens.screen_buffer,
		data->menu.screens.options_screen, 0, 0, scale);
	render_volume_sensibility(data, scale);
	put_img_to_img_scaled(&data->menu.screens.screen_buffer,
		data->menu.options_imgs.resolution[res_level], 0, 0, scale);
	render_options_overlay(data, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screens.screen_buffer.image, 0, 0);
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
