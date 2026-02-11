/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 22:41:24 by bpires-r          #+#    #+#             */
/*   Updated: 2026/02/11 23:54:41 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Clean rotation function - applies rotation to both direction and plane vectors
static void	apply_rotation(t_cub3d *data, double rotation_amount)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	// Pre-calculate trigonometric values for efficiency
	cos_rot = cos(rotation_amount);
	sin_rot = sin(rotation_amount);
	
	// Apply 2D rotation matrix to direction vector
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
	
	// Apply same rotation to camera plane vector
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos_rot - data->player.plane_y * sin_rot;
	data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y * cos_rot;
	
	// Update player angle for consistency
	data->player.angle += rotation_amount;
	
	// Keep angle in valid range [0, 2π]
	if (data->player.angle >= 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
}

// Capture mouse movement and convert to rotation amount
static double	capture_mouse_movement(t_cub3d *data)
{
	int		current_x;
	int		current_y;
	int		center_x;
	int		center_y;
	double	mouse_delta;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	
	// Get current mouse position
	mlx_mouse_get_pos(data->mlx, data->window, &current_x, &current_y);
	
	// Reset mouse to center immediately (prevents mouse from leaving window)
	mlx_mouse_move(data->mlx, data->window, center_x, center_y);
	
	// Only process if mouse moved from center and is within window bounds
	if ((current_x != center_x || current_y != center_y) && 
		current_x >= 0 && current_x <= WIDTH && 
		current_y >= 0 && current_y <= HEIGHT)
	{
		// Calculate horizontal movement from center
		mouse_delta = (double)(current_x - center_x) * MOUSE_SENSITIVITY;
		
		// Debug output
		printf("Mouse moved from center by %d pixels, rotation: %.4f\n", 
			   current_x - center_x, mouse_delta);
		
		return (mouse_delta);
	}
	
	return (0.0);  // No significant movement
}

// Main mouse rotation handler - clean and optimized
void	handle_mouse_rotation(t_cub3d *data)
{
	double	rotation_amount;
	
	// Step 1: Capture mouse movement and convert to rotation
	rotation_amount = capture_mouse_movement(data);
	
	// Step 2: Only apply rotation if there was significant movement
	if (fabs(rotation_amount) < 0.001)  // Threshold for minimum rotation
		return;
	
	// Step 3: Apply the rotation to our view direction
	apply_rotation(data, rotation_amount);
	
	// Step 4: Update stored mouse position to center
	data->mouse.x = WIDTH / 2;
	data->mouse.y = HEIGHT / 2;
	data->mouse.prev_x = WIDTH / 2;
	data->mouse.prev_y = HEIGHT / 2;
	
	printf("Rotation applied! New direction: dir_x=%.3f, dir_y=%.3f\n", 
		   data->player.dir_x, data->player.dir_y);
}

int mouse_motion_hook(int x, int y, t_cub3d *data)
{
    (void)y;  // We don't use Y coordinate for FPS camera rotation
    
    // Store current position in mouse structure (for debugging/other uses)
    data->mouse.prev_x = data->mouse.x;
    data->mouse.prev_y = data->mouse.y;  
    data->mouse.x = x;
    data->mouse.y = y;
    
    // Handle the actual rotation
    handle_mouse_rotation(data);
    
    return (0);  // Required return value for MLX hooks
}

