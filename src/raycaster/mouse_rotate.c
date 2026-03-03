/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 01:15:11 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 16:04:38 by joafaust         ###   ########.fr       */
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

// Continuous rotation based on mouse distance from center
void update_mouse_rotation(t_cub3d *data, double dt)
{
    double distance_from_center_x;
    double distance_from_center_y;
    double rotation_speed;
    double pitch_speed;
    double sensitivity_scale;
    double max_pitch_scaled;
    double sensibility_mult;
    
    // Get menu sensibility multiplier (0.5x to 2.0x)
    sensibility_mult = get_sensibility_multiplier(data->menu.options.sensibility_level);
    
    // Scale sensitivity to maintain consistent feel across resolutions
    // Standard resolution is 1920x1080 (RES_4)
    sensitivity_scale = (double)data->current_width / (double)RES_4_WIDTH;
    
    // Calculate horizontal distance from center (left/right rotation)
    distance_from_center_x = (double)(data->mouse.x - data->mouse.cx);
    
    // Calculate vertical distance from center (up/down pitch)
    distance_from_center_y = (double)(data->mouse.y - data->mouse.cy);
    
    // Handle horizontal rotation (yaw)
    if (distance_from_center_x != 0.0)
    {
        rotation_speed = distance_from_center_x * MOUSE_SENSITIVITY * sensitivity_scale * sensibility_mult * dt;
        rotate_player(data, rotation_speed);
    }
    
    // Handle vertical pitch (looking up/down)
    if (distance_from_center_y != 0.0)
    {
        pitch_speed = -distance_from_center_y * MOUSE_SENSITIVITY * sensitivity_scale * sensibility_mult * dt * 1000.0; // Scale for pixel offset
        data->player.pitch += pitch_speed;
        
        // Scale MAX_PITCH based on current resolution height
        max_pitch_scaled = MAX_PITCH * ((double)data->current_height / (double)RES_4_HEIGHT);
        
        // Constrain pitch to prevent over-rotation
        if (data->player.pitch > max_pitch_scaled)
            data->player.pitch = max_pitch_scaled;
        if (data->player.pitch < -max_pitch_scaled)
            data->player.pitch = -max_pitch_scaled;
    }
    
    // Reset mouse to center if it moved
    if (distance_from_center_x != 0.0 || distance_from_center_y != 0.0)
    {
        mlx_mouse_move(data->mlx, data->window, data->mouse.cx, data->mouse.cy);
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