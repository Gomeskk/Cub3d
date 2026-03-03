/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:32:48 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 13:06:39 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_data(t_cub3d *data)
{
    data->map.grid = NULL;
    data->map.map = NULL;
    data->map.start_point = 0;
    data->map.row_count = 0;
	data->map.col_count = 0;
    data->textures.no = NULL;
	data->textures.so = NULL;
	data->textures.ea = NULL;
	data->textures.we = NULL;
	data->textures.floor = -1;
	data->textures.ceiling = -1;
	data->window = NULL;
	data->mlx = NULL;
	data->img.image = NULL;
	data->player.vel_x = 0.0;
	data->player.vel_y = 0.0;
	data->player.pitch = 0.0;
	data->player.spawn_dir = '\0';
}

void	init_player_direction(t_cub3d *data, char spawn)
{
	printf("Initializing player direction with spawn character: '%c'\n", spawn);
	
	if (spawn == 'N')
	{
		data->player.angle = 3 * M_PI / 2;
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
		printf("Set direction: North (dir_x=0, dir_y=-1)\n");
	}
	else if (spawn == 'S')
	{
		data->player.angle = M_PI / 2;
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
		printf("Set direction: South (dir_x=0, dir_y=1)\n");
	}
	else if (spawn == 'E')
	{
		data->player.angle = 0;
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
		printf("Set direction: East (dir_x=1, dir_y=0)\n");
	}
	else if (spawn == 'W')
	{
		data->player.angle = M_PI;
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
		printf("Set direction: West (dir_x=-1, dir_y=0)\n");
	}
	else
	{
		printf("WARNING: Unknown spawn character '%c', using default North direction\n", spawn);
		data->player.angle = 3 * M_PI / 2;
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	
	printf("Final direction values: dir_x=%.3f, dir_y=%.3f, angle=%.3f\n", 
		   data->player.dir_x, data->player.dir_y, data->player.angle);
}

void	init_game(t_cub3d *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUBO MUITO FIXE");
	data->current_width = WIDTH;
	data->current_height = HEIGHT;
	data->img.image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.data = mlx_get_data_addr(data->img.image, &data->img.bpp, &data->img.size_line, &data->img.type);
	data->img.width = WIDTH;
    data->img.height = HEIGHT;
	data->tile = get_tile_size(data);
	printf("tile -> %i\n", data->tile);
	printf("x -> %f    y -> %f\n", data->player.pos_x, data->player.pos_y);
	data->player.speed = data->tile * 2.5;
	data->player.radius = data->tile / 4;
	data->player.pos_x = data->player.pos_x * data->tile + data->tile / 2.0;
	data->player.pos_y = data->player.pos_y * data->tile + data->tile / 2.0;
	printf("x doubled -> %f    y doubled -> %f\n", data->player.pos_x, data->player.pos_y);
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.s = 0;
	data->keys.w = 0;
	data->keys.shift = 0;
	data->keys.space = 0;
	data->keys.arrow_up = 0;
	data->keys.arrow_down = 0;
	data->keys.arrow_left = 0;
	data->keys.arrow_right = 0;
	data->mouse.cx = WIDTH / 2;
	data->mouse.cy = HEIGHT / 2;
	data->mouse.x = data->mouse.cx;  // Initialize current position to center
	data->mouse.y = data->mouse.cy;
	data->player.pitch = 0.0;  // Initialize pitch to center (no vertical offset)
	data->player.z_offset = 0.0;  // Initialize on ground
	data->player.vertical_velocity = 0.0;  // Initialize with no vertical movement
	data->player.is_jumping = 0;  // Initialize on ground
	init_player_direction(data, data->player.spawn_dir);
	mlx_mouse_hide(data->mlx, data->window);
}
