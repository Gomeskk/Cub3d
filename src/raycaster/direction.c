/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:15:15 by bpires-r          #+#    #+#             */
/*   Updated: 2026/01/28 18:30:34 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(t_player *player, char start_pos)
{
	if (start_pos == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66; //why 0.66? Because FOV is 66 degrees
		//why is FOV 66 degrees? because it's standard in Wolfenstein 3D
		player->plane_y = 0.0;
	}
	else if (start_pos == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (start_pos == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (start_pos == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

void rotate_player(t_player *player, double rot_angle)
{
    double old_dir_x = player->dir_x;
    double old_plane_x = player->plane_x;
    
    player->dir_x = player->dir_x * cos(rot_angle) - player->dir_y * sin(rot_angle);
    player->dir_y = old_dir_x * sin(rot_angle) + player->dir_y * cos(rot_angle);
    
    player->plane_x = player->plane_x * cos(rot_angle) - player->plane_y * sin(rot_angle);
    player->plane_y = old_plane_x * sin(rot_angle) + player->plane_y * cos(rot_angle);
}

/*
// For each screen column x (0 to screen_width):
void cast_ray(t_cub3d *data, int x)
{
    double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;  // -1 to +1
    
    // Ray direction = direction + camera_plane * camera_x
    double ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
    double ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
    
    // Now cast this ray through the map...
}*/