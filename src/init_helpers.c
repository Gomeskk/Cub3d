#include "cub3d.h"

/*
** Fill enemy animation path array in one place.
*/
static void	set_enemy_anim_paths(char **paths)
{
	paths[0] = "Png_images/Enemys/1.xpm";
	paths[1] = "Png_images/Enemys/2.xpm";
	paths[2] = "Png_images/Enemys/3.xpm";
	paths[3] = "Png_images/Enemys/4.xpm";
	paths[4] = "Png_images/Enemys/5.xpm";
	paths[5] = "Png_images/Enemys/6.xpm";
}

/*
** Load enemy animation frames and set the default enemy texture.
*/
int	load_enemy_animations(t_cub3d *data)
{
	char	*paths[ENEMY_ANIM_FRAMES];
	int		i;

	set_enemy_anim_paths(paths);
	i = 0;
	while (i < ENEMY_ANIM_FRAMES)
	{
		data->enemy_frames[i].image = mlx_xpm_file_to_image(data->mlx,
				paths[i], &data->enemy_frames[i].width,
				&data->enemy_frames[i].height);
		if (!data->enemy_frames[i].image)
			return (0);
		data->enemy_frames[i].data = mlx_get_data_addr(
				data->enemy_frames[i].image, &data->enemy_frames[i].bpp,
				&data->enemy_frames[i].size_line, &data->enemy_frames[i].type);
		if (!data->enemy_frames[i].data)
			return (0);
		i++;
	}
	data->enemy_frame_count = ENEMY_ANIM_FRAMES;
	data->enemy_anim_enabled = 1;
	data->enemy_texture = data->enemy_frames[0];
	return (1);
}

/*
** Initialize player direction for north/south spawns.
*/
void	init_player_direction_ns(t_cub3d *data, char spawn)
{
	if (spawn == 'N')
	{
		data->player.angle = 3 * M_PI / 2;
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else
	{
		data->player.angle = M_PI / 2;
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

/*
** Initialize player direction for east/west spawns.
*/
void	init_player_direction_ew(t_cub3d *data, char spawn)
{
	if (spawn == 'E')
	{
		data->player.angle = 0;
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else
	{
		data->player.angle = M_PI;
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

/*
** Initialize enemy pixel positions and finish runtime init hooks.
*/
void	init_enemy_runtime_state(t_cub3d *data)
{
	int	i;

	i = -1;
	while (++i < data->map.enemy_count)
	{
		data->map.enemies[i].pos_x = data->map.enemies[i].grid_x
			* data->tile + data->tile / 2.0;
		data->map.enemies[i].pos_y = data->map.enemies[i].grid_y
			* data->tile + data->tile / 2.0;
	}
	init_fps_counter(&data->fps);
	mlx_mouse_hide(data->mlx, data->window);
}
