/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:12:53 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 15:39:08 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycast_render(t_cub3d *data)
{
    clear_image(&data->img, 0x000000);
    int x = 0;
    while (x < data->current_width)
    {
        init_ray(data, &data->ray, x);
        perform_dda(data, &data->ray);
        draw_wall_column(data, &data->ray, x);
        x++;
    }
}

void init_ray(t_cub3d *data, t_ray *ray, int screen_x)
{
    // Calculate camera X coordinate (-1 to 1)
    ray->camera_x = 2 * screen_x / (double)data->current_width - 1;
    
    // Calculate ray direction using player direction + camera plane
    ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
    ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
    
    // Current map position (convert pixel to grid)
    ray->map_x = (int)(data->player.pos_x / data->tile);
    ray->map_y = (int)(data->player.pos_y / data->tile);
    
    // Calculate delta distances (avoid division by zero)
    if (ray->ray_dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
        
    if (ray->ray_dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
    
    ray->hit = 0;
}

void setup_dda(t_cub3d *data, t_ray *ray)
{
    // Player position in grid coordinates
    double pos_x = data->player.pos_x / data->tile;
    double pos_y = data->player.pos_y / data->tile;
    
    // Calculate step and initial side_dist
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - pos_x) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - pos_y) * ray->delta_dist_y;
    }
}

void perform_dda(t_cub3d *data, t_ray *ray)
{
    setup_dda(data, ray);
    
    // Perform DDA
    while (ray->hit == 0)
    {
        // Jump to next map square, either in x-direction, or in y-direction
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // X-side wall hit
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // Y-side wall hit
        }
        
        // Check bounds before accessing map
        if (ray->map_x < 0 || ray->map_x >= data->map.col_count || 
            ray->map_y < 0 || ray->map_y >= data->map.row_count)
        {
            ray->hit = 1; // Treat out of bounds as wall
            break;
        }
        
        // Check if ray has hit a wall
        if (data->map.grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
    
    // Calculate perpendicular wall distance
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - (data->player.pos_x / data->tile) + 
                              (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - (data->player.pos_y / data->tile) + 
                              (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void draw_wall_column(t_cub3d *data, t_ray *ray, int x)
{
    // Calculate height of line to draw on screen
    // Scale by FOV to make walls taller when zoomed in (smaller plane), shorter when zoomed out (larger plane)
    double current_plane_mag = sqrt(data->player.plane_x * data->player.plane_x + 
                                    data->player.plane_y * data->player.plane_y);
    double fov_scale = FOV_NORMAL / current_plane_mag;
    ray->line_height = (int)(data->current_height / ray->perp_wall_dist * fov_scale);
    
    // Calculate lowest and highest pixel to fill in current stripe
    // Apply pitch offset for looking up/down and z_offset for jumping
    int vertical_offset = (int)data->player.pitch + (int)data->player.z_offset;
    ray->draw_start = -ray->line_height / 2 + data->current_height / 2 + vertical_offset;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
        
    ray->draw_end = ray->line_height / 2 + data->current_height / 2 + vertical_offset;
    if (ray->draw_end >= data->current_height)
        ray->draw_end = data->current_height - 1;
    
    // Choose wall color based on side (darker for y-sides)
    int color;
    if (ray->side == 0) // X-side walls (North/South faces)
        color = 0x00FF00;
    else                // Y-side walls (East/West faces)
        color = 0x008000;
    
    // Draw ceiling (above wall) - using .cub file color
    for (int y = 0; y < ray->draw_start; y++)
        pixel_put(&data->img, x, y, data->textures.ceiling);
    
    // Draw wall
    for (int y = ray->draw_start; y < ray->draw_end; y++)
        pixel_put(&data->img, x, y, color);
    
    // Draw floor (below wall) - using .cub file color
    for (int y = ray->draw_end; y < data->current_height; y++)
        pixel_put(&data->img, x, y, data->textures.floor);
}
