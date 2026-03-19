/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:25:30 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/19 21:38:05 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Draws a horizontal border line at the specified y position.
** Fills the entire width with black pixels.
*/
static void	draw_horizontal_line(t_cub3d *data, int y)
{
	int	x;

	x = 0;
	while (x < data->current_width)
	{
		pixel_put(&data->img, x, y, 0x800080);
		x++;
	}
}

/*
** Draws the top and bottom borders of the screen.
*/
static void	draw_horizontal_borders(t_cub3d *data, int thickness)
{
	int	y;

	y = 0;
	while (y < thickness)
	{
		draw_horizontal_line(data, y);
		y++;
	}
	y = data->current_height - thickness;
	while (y < data->current_height)
	{
		draw_horizontal_line(data, y);
		y++;
	}
}

/*
** Draws the left and right borders at the specified y position.
** Only draws the vertical edges, not the full width.
*/
static void	draw_vertical_edges(t_cub3d *data, int y, int thickness)
{
	int	x;

	x = 0;
	while (x < thickness)
	{
		pixel_put(&data->img, x, y, 0x800080);
		x++;
	}
	x = data->current_width - thickness;
	while (x < data->current_width)
	{
		pixel_put(&data->img, x, y, 0x800080);
		x++;
	}
}

/*
** Draws a black border around the entire screen during gameplay.
** Border thickness scales with screen height.
** Draws top, bottom, left, and right borders as solid black rectangles.
*/
void	draw_screen_border(t_cub3d *data)
{
	int	y;
	int	thickness;

	thickness = data->current_height / 90;
	if (thickness < 1)
		thickness = 1;
	draw_horizontal_borders(data, thickness);
	y = thickness;
	while (y < data->current_height - thickness)
	{
		draw_vertical_edges(data, y, thickness);
		y++;
	}
}
