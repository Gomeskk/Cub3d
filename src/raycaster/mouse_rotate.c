/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 01:15:11 by bpires-r          #+#    #+#             */
/*   Updated: 2026/02/12 02:47:30 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void rotate_player(t_cub3d *data, double angle)
{
    double old_dirx;
    double old_diry;
    //double old_planex;

    old_dirx = data->player.dir_x;
    old_diry = data->player.dir_y;
    //old_planex = data->player.plane_x;
    
    data->player.dir_x = old_dirx * cos(angle) - old_diry * sin(angle);
    data->player.dir_y = old_dirx * sin(angle) + old_diry * cos(angle);

    //if theres a camera plane rotate it too this is later for raycast btw
    //data->player.plane_x = old_planex * cos(angle) - data->player.plane_y * sin(angle);
    //data->player.plane_y = old_planex * sin(angle) + data->player.plane_y * cos(angle);
}

// Continuous rotation based on mouse distance from center
void update_mouse_rotation(t_cub3d *data, double dt)
{
    double distance_from_center;
    double rotation_speed;
    
    // Calculate horizontal distance from center
    distance_from_center = (double)(data->mouse.x - data->mouse.cx);
    
    // Only rotate if mouse is not at center
    if (distance_from_center != 0.0)
    {
        // Calculate rotation speed: distance * sensitivity * delta_time
        rotation_speed = distance_from_center * MOUSE_SENSITIVITY * dt;
		mlx_mouse_move(data->mlx, data->window, data->mouse.cx, data->mouse.cy);
        rotate_player(data, rotation_speed);
    }
}

//mouse motion event handler - tracks position only
int mouse_moved(int x, int y, t_cub3d *data)
{
    // Update mouse position for distance calculation
    data->mouse.x = x;
    data->mouse.y = y;
    return (0);
}