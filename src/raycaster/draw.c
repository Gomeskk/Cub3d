/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:26:51 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 00:41:04 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_player_dot(t_img *img, int cx, int cy, int color)
{
	int	x;
	int	y;
	int	rr;

	rr = 3 * 3;
	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if (x * x + y * y <= rr)
				pixel_put(img, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || y >= img->height || x >= img->width)
		return ;
	pixel = img->data + (y * img->size_line + (x * img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	put_color_tile(t_img *screen, int pos[2], int color, int tile)
{
	int	y;
	int	x;

	y = 0;
	while (y < tile)
	{
		x = 0;
		while (x < tile)
		{
			pixel_put(screen, pos[0] + x, pos[1] + y, color);
			x++;
		}
		y++;
	}
}
