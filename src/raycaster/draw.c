/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:26:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/16 19:45:02 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_player_dot(t_img *img, int cx, int cy, int radius, int color)
{
    int x;
    int y;
    int rr;

    rr = radius * radius;
    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= rr)
                pixel_put(img, cx + x, cy + y, color);
            x++;
        }
        y++;
    }
}

void	draw_minimap(t_cub3d *data)
{
	int	x;
	int	y;
	int	color;

	clear_image(&data->img, 0x000000);
	y = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == '1') color = 0x444444;
			else if (data->map.grid[y][x] == '0') color = 0xAAAAAA;
			else
				color = 0x000000;
			put_color_tile(&data->img, x * data->tile, y * data->tile, color, data->tile);
			x++;
		}
		y++;
	}
	put_player_dot(&data->img, data->player.pos_x, data->player.pos_y,data->player.radius, 0x00FF00);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	if (x < 0 || y < 0 || y >= img->height || x >= img->width)
		return ;
	pixel = img->data + (y * img->size_line + (x * img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	put_color_tile(t_img *screen, int pos_x, int pos_y, int color, int tile)
{
	int		y;
	int		x;
	
	y = 0;
	while (y < tile)
	{
		x = 0;
		while (x < tile)
		{
			pixel_put(screen, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}
