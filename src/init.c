/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:32:48 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/16 19:50:50 by bpires-r         ###   ########.fr       */
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
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUBO MUITO FIXE");
	data->img.image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.data = mlx_get_data_addr(data->img.image, &data->img.bpp, &data->img.size_line, &data->img.type);
	data->img.width = WIDTH;
    data->img.height = HEIGHT;
	data->tile = get_tile_size(data);
	printf("tile -> %i\n", data->tile);
	printf("x -> %f    y -> %f\n", data->player.pos_x, data->player.pos_y);
	data->player.speed = 180.0;
	data->player.radius = data->tile / 4;
	data->player.pos_x = data->player.pos_x * data->tile + data->tile / 2.0;
	data->player.pos_y = data->player.pos_y * data->tile + data->tile / 2.0;
	printf("x doubled -> %f    y doubled -> %f\n", data->player.pos_x, data->player.pos_y);
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.s = 0;
	data->keys.w = 0;
}
