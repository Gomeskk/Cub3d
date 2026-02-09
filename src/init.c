/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:32:48 by bpires-r          #+#    #+#             */
/*   Updated: 2026/02/06 16:59:53 by bpires-r         ###   ########.fr       */
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
}

void	init_game(t_cub3d *data)
{
	data->img.image = mlx_new_image(data->mlx, data->current_width, data->current_height);
	data->img.data = mlx_get_data_addr(data->img.image, &data->img.bpp, &data->img.size_line, &data->img.type);
	data->img.width = data->current_width;
    data->img.height = data->current_height;
	data->tile = get_tile_size(data);
	printf("tile -> %i\n", data->tile);
	printf("x -> %f    y -> %f\n", data->player.pos_x, data->player.pos_y);
	data->player.speed = 180.0;
	data->player.radius = data->tile / 4;
	data->player.pos_x = data->player.pos_x * data->tile + data->tile / 2.0;
	data->player.pos_y = data->player.pos_y * data->tile + data->tile / 2.0;
	//printf("Starting direction character: '%c'\n", data->map.direction);
	init_player_direction(&data->player, data->map.direction);
	//printf("Direction vectors: dir_x=%.2f, dir_y=%.2f, plane_x=%.2f, plane_y=%.2f\n", 
    //   data->player.dir_x, data->player.dir_y, data->player.plane_x, data->player.plane_y);
	//printf("x doubled -> %f    y doubled -> %f\n", data->player.pos_x, data->player.pos_y);
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.s = 0;
	data->keys.w = 0;
	data->keys.w = 0;
	data->mouse.x = data->current_width / 2;
	data->mouse.y = data->current_height / 2;
	data->mouse.prev_x = data->current_width / 2;
	data->mouse.prev_y = data->current_height / 2;
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, data->current_width / 2, data->current_height / 2);
}
