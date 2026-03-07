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
	int		r;
	char	**grid;

	i = 0;
	r = 0;
	grid = malloc(sizeof(char *) * (data->map.row_count + 1));
	if (!grid)
		return (NULL);
	while (i < data->map.row_count)
	{
		grid[i] = malloc(data->map.col_count + 1);
		if (!grid[i])
		{
			while (--i >= 0)
                free(grid[i]);
            free(grid);
			return (NULL);
		}
		i++;
	}
	grid[data->map.row_count] = NULL;
	while (r < data->map.row_count)
	{
		//copia a linha e coloca ' ' no lugar do que falta ate atingir o data->map.col_count
		//para criar uma grid rectangular :D
		copy_line(&grid[r], data->map.map[data->map.start + r], data->map.col_count);
		r++;
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
		//alterar nome de col count e row count para max_x e max_y
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
int has_space_neighbor(char **g, int r, int c)
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

int	parse_map(t_cub3d *data)
{
	if (!data->map.map || !data->map.map[data->map.start])
		return (0);
	data->map.row_count = 0;
	//get max len NON RECTANGULAR MAP >:C
	while (data->map.map[data->map.start + data->map.row_count])
	{
		if ((int)ft_strlen(data->map.map[data->map.start + data->map.row_count]) > data->map.col_count)
			data->map.col_count = ft_strlen(data->map.map[data->map.start + data->map.row_count]);
		data->map.row_count++;
	}
	//creating rectangular map #retangulo #espaçosparaomax_x
	data->map.grid = build_grid(data);
	if (!data->map.grid)
		return (0);
	//scan pelo mapa para validaçao e spawn
	if (!validate_map_chars(data)
		|| !is_closed(data)
		|| data->map.start_point != 1)
		return (exit_error(data, PLAYER_POINT), 0);
	
	// Initialize doors after map is validated
	init_doors(data);
	if (data->map.doors)
		store_door_positions(data);
	// Initialize buttons after map is validated
	init_buttons(data);
	if (data->map.buttons)
		store_button_positions(data);
	
	return (1);
}
