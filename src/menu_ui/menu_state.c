#include "../../inc/cub3d.h"

/*
** Initialize all menu images
** Loads XPM files for: start menu, difficulty selection, options screen
** Creates screen_buffer image - this is the compositing buffer where
** all menu elements are drawn before displaying to window
** DOUBLE BUFFERING: Prevents flickering by drawing to buffer first
*/
int	init_menu_images(t_cub3d *data)
{
	if (init_start_game_images(data) == -1)
		return (-1);
	if (init_difficulty_images(data) == -1)
		return (-1);
	if (init_skin_select_images(data) == -1)
		return (-1);
	if (init_options_images(data) == -1)
		return (-1);
	data->menu.screens.screen_buffer.image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->menu.screens.screen_buffer.image)
		return (-1);
	data->menu.screens.screen_buffer.data = mlx_get_data_addr(
			data->menu.screens.screen_buffer.image,
			&data->menu.screens.screen_buffer.bpp,
			&data->menu.screens.screen_buffer.size_line,
			&data->menu.screens.screen_buffer.endian);
	data->menu.screens.screen_buffer.width = WIDTH;
	data->menu.screens.screen_buffer.height = HEIGHT;
	return (0);
}

void	init_menu_state(t_cub3d *data)
{
	data->menu.menu_choice = MENU_START;
	data->menu.difficulty_choice = DIFF_MEDIUM;
	data->menu.skin_choice = 0;
	data->menu.last_skin_arrow_direction = 1;
	data->menu.options.sensibility_level = SENSIBILITY_DEFAULT;
	data->menu.options.volume_level = VOLUME_DEFAULT;
	data->menu.options.resolution_level = RESOLUTION_DEFAULT;
	data->menu.options.resolution_arrow_count = 0;
	data->menu.options.last_arrow_direction = ARROW_DIRECTION_DOWN;
	data->menu.options.section = SECTION_SOUND;
	data->menu.options.resolution_confirm_active = 0;
	data->menu.options.resolution_confirm_choice = 0;
	data->menu.options.pending_resolution_level = RESOLUTION_DEFAULT;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->status = MAIN_MENU_SCREEN;
}

/*
** Cleanup menu screen images
** Destroys main menu, difficulty, and options screen images
*/
static void	cleanup_menu_screens(t_cub3d *data)
{
	if (data->menu.screens.start_normal.image)
		mlx_destroy_image(data->mlx, data->menu.screens.start_normal.image);
	if (data->menu.screens.start_hover.image)
		mlx_destroy_image(data->mlx, data->menu.screens.start_hover.image);
	if (data->menu.screens.start_selected.image)
		mlx_destroy_image(data->mlx, data->menu.screens.start_selected.image);
	if (data->menu.screens.credits_screen.image)
		mlx_destroy_image(data->mlx, data->menu.screens.credits_screen.image);
	if (data->menu.difficulty.easy.image)
		mlx_destroy_image(data->mlx, data->menu.difficulty.easy.image);
	if (data->menu.difficulty.medium.image)
		mlx_destroy_image(data->mlx, data->menu.difficulty.medium.image);
	if (data->menu.difficulty.hard.image)
		mlx_destroy_image(data->mlx, data->menu.difficulty.hard.image);
	if (data->menu.screens.options_screen.image)
		mlx_destroy_image(data->mlx, data->menu.screens.options_screen.image);
	if (data->menu.options_imgs.tab_sound.image)
		mlx_destroy_image(data->mlx, data->menu.options_imgs.tab_sound.image);
	if (data->menu.options_imgs.tab_resolution.image)
		mlx_destroy_image(data->mlx, data->menu.options_imgs.tab_resolution.image);
	if (data->menu.options_imgs.tab_sensibility.image)
		mlx_destroy_image(data->mlx, data->menu.options_imgs.tab_sensibility.image);
	if (data->menu.screens.screen_buffer.image)
		mlx_destroy_image(data->mlx, data->menu.screens.screen_buffer.image);
}

/*
** Cleanup menu image arrays
** Destroys all volume and sensibility level images
*/
static void	cleanup_menu_arrays(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < VOLUME_COUNT)
	{
		if (data->menu.options_imgs.volume[i].image)
			mlx_destroy_image(data->mlx, data->menu.options_imgs.volume[i].image);
		i++;
	}
	i = 0;
	while (i < SENSIBILITY_COUNT)
	{
		if (data->menu.options_imgs.sensibility[i].image)
			mlx_destroy_image(data->mlx, data->menu.options_imgs.sensibility[i].image);
		i++;
	}
}

void	cleanup_menu(t_cub3d *data)
{
	cleanup_menu_screens(data);
	cleanup_menu_arrays(data);
}
