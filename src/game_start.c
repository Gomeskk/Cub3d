/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2026/02/12 00:28:59 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

static int	render_game(t_cub3d *data)
{
	static double	time;
	
	time += get_delta_time();
	if (time >= 1.0 / FPS)
	{
		player_movement(data, time);
		draw_minimap(data);
		mlx_clear_window(data->mlx, data->window);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
		time = 0;
	}
	return (0);
}

void	game_start(t_cub3d *data)
{
	init_game(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	mlx_hook(data->window, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->window, 3, 1L << 1, key_released, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_loop_hook(data->mlx, render_game, data);
	mlx_loop(data->mlx);
}

