/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:20:36 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:20:37 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_buttons(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.button_count = 0;
	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'B')
				data->map.button_count++;
			x++;
		}
		y++;
	}
	if (data->map.button_count == 0)
	{
		data->map.buttons = NULL;
		return ;
	}
	data->map.buttons = malloc(sizeof(t_button) * data->map.button_count);
}

void	store_button_positions(t_cub3d *data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'B')
			{
				data->map.buttons[i].x = x;
				data->map.buttons[i].y = y;
				data->map.buttons[i].is_activated = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

int	is_button(t_cub3d *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.button_count)
	{
		if (data->map.buttons[i].x == x && data->map.buttons[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

static void	swap_to_alternate(t_cub3d *data)
{
	t_wall_textures	*wt;
	t_img			temp;

	wt = &data->wall_textures;
	if (wt->textures_swapped)
		return ;
	temp = wt->alt_north;
	wt->alt_north = wt->north;
	wt->alt_south = wt->south;
	wt->alt_east = wt->east;
	wt->alt_west = wt->west;
	wt->alt_button = wt->button;
	wt->north = temp;
	wt->south = temp;
	wt->east = temp;
	wt->west = temp;
	wt->button = temp;
	wt->textures_swapped = 1;
}

void	activate_button(t_cub3d *data)
{
	int		grid_x;
	int		grid_y;
	int		i;
	double	dist;

	grid_x = (int)(data->player.pos_x / data->tile);
	grid_y = (int)(data->player.pos_y / data->tile);
	i = 0;
	while (i < data->map.button_count)
	{
		dist = sqrt(pow(data->map.buttons[i].x - grid_x, 2)
				+ pow(data->map.buttons[i].y - grid_y, 2));
		if (dist < 1.5 && !data->map.buttons[i].is_activated)
		{
			data->map.buttons[i].is_activated = 1;
			swap_to_alternate(data);
			return ;
		}
		i++;
	}
}
