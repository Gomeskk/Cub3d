/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:25:34 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/16 15:16:49 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_name(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != '.')
		i++;
	while (map[i])
	{
		if (!ft_strcmp(&map[i], ".cub") && !map[i + 4])
			return (1);
		i++;
	}
	return (0);	
}

void	check_spawn(t_cub3d *data, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->map.start_point++;
		data->player.pos_x = x;
		data->player.pos_y = y;
		data->player.spawn_dir = c;
		data->map.grid[y][x] = '0';
	}
}

int	is_closed(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count)
		{
			if (data->map.grid[y][x] == '0' || data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'S'
				|| data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'W'
				|| data->map.grid[y][x] == 'F')
			{
				if (y == 0 || y == data->map.row_count - 1 || x == 0 || x == data->map.col_count - 1)
					return (ft_putendl_fd(NO_CLOSED, 2), exit_error(data, EXAMPLE), 0);
				if (has_space_neighbor(data->map.grid, y, x))
					return (ft_putendl_fd(NO_CLOSED, 2), exit_error(data, EXAMPLE), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	indetifier_checker(t_cub3d *data)
{
	if (!data->textures.no || data->textures.no[0] == '1')
		ft_putendl_fd(NO_MISSING, 2);
	if (!data->textures.so || data->textures.so[0] == '1')
		ft_putendl_fd(SO_MISSING, 2);
	if (!data->textures.ea || data->textures.ea[0] == '1')
		ft_putendl_fd(EA_MISSING, 2);
	if (!data->textures.we || data->textures.we[0] == '1')
		ft_putendl_fd(WE_MISSING, 2);
	if (data->textures.ceiling == -1)
		ft_putendl_fd(C_MISSING, 2);
	if (data->textures.floor == -1)
		ft_putendl_fd(F_MISSING, 2);
	if (!data->textures.no || data->textures.no[0] == '1' ||  !data->textures.so || data->textures.so[0] == '1' || !data->textures.we || data->textures.we[0] == '1' || !data->textures.ea || data->textures.ea[0] == '1' || data->textures.ceiling == -1 || data->textures.floor == -1)
	{
		ft_putendl_fd(TEXTURES, 2);
		exit_error(data, EXAMPLE);
	}
}
