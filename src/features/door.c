/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:20:30 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:20:31 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_doors(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.door_count = 0;
	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'D')
				data->map.door_count++;
			x++;
		}
		y++;
	}
	if (data->map.door_count == 0)
	{
		data->map.doors = NULL;
		return ;
	}
	data->map.doors = malloc(sizeof(t_door) * data->map.door_count);
}

void	store_door_positions(t_cub3d *data)
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
			if (data->map.grid[y][x] == 'D')
			{
				data->map.doors[i].x = x;
				data->map.doors[i].y = y;
				data->map.doors[i].is_open = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

int	is_door_open(t_cub3d *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (data->map.doors[i].is_open);
		i++;
	}
	return (0);
}

static int	check_door_in_view(t_cub3d *data, int i, double *dist)
{
	double	to_door_x;
	double	to_door_y;
	double	dot;

	to_door_x = data->map.doors[i].x + 0.5;
	to_door_x -= (data->player.pos_x / data->tile);
	to_door_y = data->map.doors[i].y + 0.5;
	to_door_y -= (data->player.pos_y / data->tile);
	*dist = sqrt(to_door_x * to_door_x + to_door_y * to_door_y);
	if (*dist <= 0.0)
		return (0);
	dot = (to_door_x * data->player.dir_x + to_door_y * data->player.dir_y)
		/ *dist;
	if (*dist < 1.0 && dot > 0.8)
		return (1);
	return (0);
}

void	toggle_door(t_cub3d *data)
{
	int		i;
	double	dist;

	i = 0;
	while (i < data->map.door_count)
	{
		if (check_door_in_view(data, i, &dist))
		{
			data->map.doors[i].is_open = !data->map.doors[i].is_open;
			return ;
		}
		i++;
	}
}
