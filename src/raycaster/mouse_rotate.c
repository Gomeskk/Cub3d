/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 01:15:11 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/10 23:07:15 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void rotate_player(t_cub3d *data, double angle)
{
    double old_dirx;
    double old_diry;
    double old_planex;

    old_dirx = data->player.dir_x;
    old_diry = data->player.dir_y;
    old_planex = data->player.plane_x;
    
    data->player.dir_x = old_dirx * cos(angle) - old_diry * sin(angle);
    data->player.dir_y = old_dirx * sin(angle) + old_diry * cos(angle);

    // CRITICAL: Camera plane MUST rotate with direction for raycasting to work
    data->player.plane_x = old_planex * cos(angle) - data->player.plane_y * sin(angle);
    data->player.plane_y = old_planex * sin(angle) + data->player.plane_y * cos(angle);
}

#include <unistd.h>
#include <stdio.h>

// Continuous rotation based on mouse distance from center
void update_mouse_rotation(t_cub3d *data, double dt)
{
    double distance_from_center_x;
    double distance_from_center_y;
    double rotation_speed;
    double pitch_speed;
    double sensibility_mult;
    
    // Get menu sensibility multiplier (0.5x to 2.0x)
    sensibility_mult = get_sensibility_multiplier(data->menu.options.sensibility_level);
    
    // Calculate horizontal distance from center (left/right rotation)
    distance_from_center_x = (double)(data->mouse.x - data->mouse.cx);
    
    // Calculate vertical distance from center (up/down pitch)
    distance_from_center_y = (double)(data->mouse.y - data->mouse.cy);
    
    // Handle horizontal rotation (yaw)
    // No resolution scaling - same pixel movement = same rotation at any resolution
    if (distance_from_center_x != 0.0)
    {
        rotation_speed = distance_from_center_x * MOUSE_SENSITIVITY * sensibility_mult * dt;
        rotate_player(data, rotation_speed);
    }
    
    // Handle vertical pitch (looking up/down)
    if (distance_from_center_y != 0.0)
    {
        pitch_speed = -distance_from_center_y * MOUSE_SENSITIVITY * sensibility_mult * dt * 1000.0; // Scale for pixel offset
        data->player.pitch += pitch_speed;
        
        // Constrain pitch to prevent over-rotation (same limit at all resolutions)
        if (data->player.pitch > MAX_PITCH)
            data->player.pitch = MAX_PITCH;
        if (data->player.pitch < -MAX_PITCH)
            data->player.pitch = -MAX_PITCH;
    }
    
    // Reset mouse to center if it moved
    if (distance_from_center_x != 0.0 || distance_from_center_y != 0.0)
    {
        mlx_mouse_move(data->mlx, data->window, data->mouse.cx, data->mouse.cy);
        write(1, "\033[1;1H", 7);
    write(1, "\033[2J", 7);
    printf("Mouse moved:\nx=%d, y=%d\ndistance_x=%.2f, distance_y=%.2f\nrotation_speed=%.4f, pitch_speed=%.4f\n",
           data->mouse.x, data->mouse.y, distance_from_center_x, distance_from_center_y, rotation_speed, pitch_speed);
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