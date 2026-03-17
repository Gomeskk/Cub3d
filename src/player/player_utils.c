/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:19:40 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/17 18:54:57 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blocking_cell(t_cub3d *data, int row, int col)
{
	if (data->map.grid[row][col] == '1' || data->map.grid[row][col] == 'B')
		return (1);
	if (data->map.grid[row][col] == 'D' && !is_door_open(data, col, row))
		return (1);
	return (0);
}

void	cycle_fov(t_cub3d *data)
{
	double	fov_value;
	double	plane_magnitude;
	double	old_plane_x;
	double	old_plane_y;

	old_plane_x = data->player.plane_x;
	old_plane_y = data->player.plane_y;
	plane_magnitude = sqrt(old_plane_x * old_plane_x
			+ old_plane_y * old_plane_y);
	if (plane_magnitude < 0.001)
		return ;
	data->player.fov_level = (data->player.fov_level + 1) % 3;
	if (data->player.fov_level == 0)
		fov_value = FOV_NORMAL;
	else if (data->player.fov_level == 1)
		fov_value = FOV_NARROW;
	else
		fov_value = FOV_WIDE;
	data->player.plane_x = (old_plane_x / plane_magnitude) * fov_value;
	data->player.plane_y = (old_plane_y / plane_magnitude) * fov_value;
}

double	get_time_in_seconds(void)
{
	struct timespec	ts;

	clock_gettime(1, &ts);
	return (ts.tv_sec + ts.tv_nsec / 1e9);
}

double	get_delta_time(void)
{
	static double	last = 0.0;
	double			dt;
	double			now;

	now = get_time_in_seconds();
	if (last == 0.0)
	{
		last = now;
		return (0.0);
	}
	dt = now - last;
	last = now;
	return (dt);
}
