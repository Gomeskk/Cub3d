/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:23:51 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/09 01:58:16 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**build_grid(t_cub3d *data)
{
	int		i;
	char	**grid;

	i = 0;
	grid = ft_calloc(data->map.row_count + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	while (i < data->map.row_count)
	{
		grid[i] = malloc(data->map.col_count + 1);
		if (!grid[i])
			return (free_ar((void **)grid), NULL);
		copy_line(&grid[i], data->map.map[data->map.start + i],
			data->map.col_count);
		i++;
	}
	return (grid);
}

static int	validate_map_chars(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count)
		{
			if (!is_map_line(data->map.grid[y][x]))
				return (exit_error(data, WRONG_CHAR), 0);
			check_spawn(data, data->map.grid[y][x], x, y);
			x++;
		}
		y++;
	}
	return (1);
}

int	has_space_neighbor(char **g, int r, int c)
{
	if (g[r - 1][c] == ' ')
		return (1);
	if (g[r + 1][c] == ' ')
		return (1);
	if (g[r][c - 1] == ' ')
		return (1);
	if (g[r][c + 1] == ' ')
		return (1);
	return (0);
}

static void	init_map_entities(t_cub3d *data)
{
	init_doors(data);
	if (data->map.doors)
		store_door_positions(data);
	init_buttons(data);
	if (data->map.buttons)
		store_button_positions(data);
	init_enemies(data);
	if (data->map.enemies)
		store_enemy_positions(data);
}

int	parse_map(t_cub3d *data)
{
	if (!data->map.map || !data->map.map[data->map.start])
		return (0);
	data->map.row_count = 0;
	while (data->map.map[data->map.start + data->map.row_count])
	{
		if ((int)ft_strlen(data->map.map[data->map.start
					+ data->map.row_count]) > data->map.col_count)
			data->map.col_count = ft_strlen(data->map.map
				[data->map.start + data->map.row_count]);
		data->map.row_count++;
	}
	data->map.grid = build_grid(data);
	if (!data->map.grid)
		return (0);
	if (!validate_map_chars(data)
		|| !is_closed(data)
		|| data->map.start_point != 1)
		return (exit_error(data, PLAYER_POINT), 0);
	init_map_entities(data);
	return (1);
}
