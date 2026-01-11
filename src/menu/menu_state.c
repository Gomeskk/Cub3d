#include "../../inc/cub3d.h"

int	init_menu_images(t_cub3d *data)
{
	if (init_start_game_images(data) == -1)
		return (-1);
	if (init_difficulty_images(data) == -1)
		return (-1);
	if (init_options_images(data) == -1)
		return (-1);
	data->menu.screen_buffer.image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->menu.screen_buffer.image)
		return (-1);
	data->menu.screen_buffer.data = mlx_get_data_addr(
			data->menu.screen_buffer.image, &data->menu.screen_buffer.bpp,
			&data->menu.screen_buffer.size_line, &data->menu.screen_buffer.endian);
	data->menu.screen_buffer.width = WIDTH;
	data->menu.screen_buffer.height = HEIGHT;
	return (0);
}

void	init_menu_state(t_cub3d *data)
{
	data->menu.menu_choice = MENU_START;
	data->menu.difficulty_choice = DIFF_MEDIUM;
	data->menu.sensibility_level = SENSIBILITY_DEFAULT;
	data->menu.volume_level = VOLUME_DEFAULT;
	data->menu.resolution_level = RESOLUTION_DEFAULT;
	data->menu.resolution_arrow_count = 0;
	data->menu.last_arrow_direction = ARROW_DIRECTION_DOWN;
	data->menu.options_section = SECTION_SOUND;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->status = MAIN_MENU_SCREEN;
}

void	cleanup_menu(t_cub3d *data)
{
	int	i;

	if (data->menu.start_normal.image)
		mlx_destroy_image(data->mlx, data->menu.start_normal.image);
	if (data->menu.start_hover.image)
		mlx_destroy_image(data->mlx, data->menu.start_hover.image);
	if (data->menu.start_selected.image)
		mlx_destroy_image(data->mlx, data->menu.start_selected.image);
	if (data->menu.diff_easy.image)
		mlx_destroy_image(data->mlx, data->menu.diff_easy.image);
	if (data->menu.diff_medium.image)
		mlx_destroy_image(data->mlx, data->menu.diff_medium.image);
	if (data->menu.diff_hard.image)
		mlx_destroy_image(data->mlx, data->menu.diff_hard.image);
	if (data->menu.options_screen.image)
		mlx_destroy_image(data->mlx, data->menu.options_screen.image);
	if (data->menu.tab_sound.image)
		mlx_destroy_image(data->mlx, data->menu.tab_sound.image);
	if (data->menu.tab_resolution.image)
		mlx_destroy_image(data->mlx, data->menu.tab_resolution.image);
	if (data->menu.tab_sensibility.image)
		mlx_destroy_image(data->mlx, data->menu.tab_sensibility.image);
	if (data->menu.screen_buffer.image)
		mlx_destroy_image(data->mlx, data->menu.screen_buffer.image);
	i = 0;
	while (i < VOLUME_COUNT)
	{
		if (data->menu.volume[i].image)
			mlx_destroy_image(data->mlx, data->menu.volume[i].image);
		i++;
	}
	i = 0;
	while (i < SENSIBILITY_COUNT)
	{
		if (data->menu.sensibility[i].image)
			mlx_destroy_image(data->mlx, data->menu.sensibility[i].image);
		i++;
	}
}
