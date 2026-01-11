#include "../../inc/cub3d.h"

static float	get_scale(t_cub3d *data)
{
	return ((float)data->current_width / (float)RES_4_WIDTH);
}

void	render_main_menu(t_cub3d *data)
{
	t_menu_img	*img;
	float		scale;

	scale = get_scale(data);
	mlx_clear_window(data->mlx, data->window);
	if (data->menu.menu_choice == MENU_START)
		img = &data->menu.start_normal;
	else if (data->menu.menu_choice == MENU_OPTIONS)
		img = &data->menu.start_hover;
	else
		img = &data->menu.start_selected;
	put_img_to_img_scaled(&data->menu.screen_buffer, *img, 0, 0, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screen_buffer.image, 0, 0);
}

void	render_difficulty_menu(t_cub3d *data)
{
	t_menu_img	*img;
	float		scale;

	scale = get_scale(data);
	mlx_clear_window(data->mlx, data->window);
	if (data->menu.difficulty_choice == DIFF_EASY)
		img = &data->menu.diff_easy;
	else if (data->menu.difficulty_choice == DIFF_MEDIUM)
		img = &data->menu.diff_medium;
	else
		img = &data->menu.diff_hard;
	put_img_to_img_scaled(&data->menu.screen_buffer, *img, 0, 0, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screen_buffer.image, 0, 0);
}

static void	render_resolution_confirm(t_cub3d *data, float scale)
{
	if (data->menu.resolution_confirm_choice == 0)
		put_img_to_img_scaled(&data->menu.screen_buffer,
			data->menu.resolution_decline, 0, 0, scale);
	else
		put_img_to_img_scaled(&data->menu.screen_buffer,
			data->menu.resolution_approve, 0, 0, scale);
}

static void	render_resolution_section(t_cub3d *data, float scale)
{
	put_img_to_img_scaled(&data->menu.screen_buffer,
		data->menu.tab_resolution, 0, 0, scale);
	if (data->menu.resolution_confirm_active)
		render_resolution_confirm(data, scale);
	else if (data->menu.last_arrow_direction == -1)
		put_img_to_img_scaled(&data->menu.screen_buffer,
			data->menu.arrow_down, 0, 0, scale);
	else
		put_img_to_img_scaled(&data->menu.screen_buffer,
			data->menu.arrow_up, 0, 0, scale);
}

static void	render_options_overlay(t_cub3d *data, float scale)
{
	if (data->menu.options_section == SECTION_SOUND)
		put_img_to_img_scaled(&data->menu.screen_buffer,
			data->menu.tab_sound, 0, 0, scale);
	else if (data->menu.options_section == SECTION_RESOLUTION)
		render_resolution_section(data, scale);
	else if (data->menu.options_section == SECTION_SENSIBILITY)
		put_img_to_img_scaled(&data->menu.screen_buffer,
			data->menu.tab_sensibility, 0, 0, scale);
}

static void	render_volume_sensibility(t_cub3d *data, float scale)
{
	int	vol_x;
	int	vol_y;
	int	sens_x;
	int	sens_y;

	vol_x = (int)(VOLUME_IMG_X * scale);
	vol_y = (int)(VOLUME_IMG_Y * scale);
	sens_x = (int)(SENSIBILITY_IMG_X * scale);
	sens_y = (int)(SENSIBILITY_IMG_Y * scale);
	put_img_to_img_scaled(&data->menu.screen_buffer,
		data->menu.volume[data->menu.volume_level], vol_x, vol_y, scale);
	put_img_to_img_scaled(&data->menu.screen_buffer,
		data->menu.sensibility[data->menu.sensibility_level],
		sens_x, sens_y, scale);
}

void	render_credits(t_cub3d *data)
{
	float	scale;
	int		res_level;

	scale = get_scale(data);
	res_level = data->menu.pending_resolution_level;
	put_img_to_img_scaled(&data->menu.screen_buffer,
		data->menu.options_screen, 0, 0, scale);
	render_volume_sensibility(data, scale);
	put_img_to_img_scaled(&data->menu.screen_buffer,
		data->menu.resolution[res_level], 0, 0, scale);
	render_options_overlay(data, scale);
	mlx_put_image_to_window(data->mlx, data->window,
		data->menu.screen_buffer.image, 0, 0);
}
