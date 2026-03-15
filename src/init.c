/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:32:48 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/15 23:29:56 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initialize core data defaults before parsing and resource loading.
*/
void	init_data(t_cub3d *data)
{
	ft_bzero(data, sizeof(t_cub3d));
	data->textures.floor = -1;
	data->textures.ceiling = -1;
	data->textures.button = NULL;
	data->textures.alt_texture = NULL;
	data->game_settings.difficulty_mult = 1.0;
}

void	init_player_direction(t_cub3d *data, char spawn)
{
	if (spawn == 'N' || spawn == 'S')
		init_player_direction_ns(data, spawn);
	else if (spawn == 'E' || spawn == 'W')
		init_player_direction_ew(data, spawn);
	else
	{
		data->player.angle = 3 * M_PI / 2;
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
}

/*
** Initialize runtime gameplay values after resources are loaded.
*/
static void	init_runtime_state(t_cub3d *data)
{
	data->tile = get_tile_size(data);
	data->player.speed = data->tile * 2.5;
	data->player.radius = data->tile / 4;
	data->player.pos_x = data->player.pos_x * data->tile + data->tile / 2.0;
	data->player.pos_y = data->player.pos_y * data->tile + data->tile / 2.0;
	ft_bzero(&data->keys, sizeof(t_keys));
	data->mouse.cx = WIDTH / 2;
	data->mouse.cy = HEIGHT / 2;
	data->mouse.x = data->mouse.cx;
	data->mouse.y = data->mouse.cy;
	data->player.pitch = 0.0;
	data->player.z_offset = 0.0;
	data->player.vertical_velocity = 0.0;
	data->player.is_jumping = 0;
	data->player.minimap_visible = 1;
	data->player.fov_level = 0;
	init_player_direction(data, data->player.spawn_dir);
	init_enemy_runtime_state(data);
}

/*
** Initialize mlx resources and gameplay state before entering the loop.
*/
void	init_game(t_cub3d *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUBO MUITO FIXE");
	data->current_width = WIDTH;
	data->current_height = HEIGHT;
	data->img.image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.data = mlx_get_data_addr(data->img.image, &data->img.bpp,
			&data->img.size_line, &data->img.type);
	data->img.width = WIDTH;
	data->img.height = HEIGHT;
	if (!load_wall_textures(data))
		exit_error(data, "Failed to load wall textures");
	data->z_buffer = malloc(sizeof(double) * WIDTH);
	if (!data->z_buffer)
		exit_error(data, "Failed to allocate z_buffer");
	if (!load_enemy_animations(data))
		exit_error(data, "Failed to load enemy animation textures");
	init_runtime_state(data);
}
