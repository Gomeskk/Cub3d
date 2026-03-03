/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:24:19 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/03 16:43:45 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	circle_intersects_rectangle(t_cub3d *data, double cx, double cy, int row, int col)
{
	double	rect_x;
	double	rect_y;
	double	dx;
	double	dy;

	rect_x = (double)col * (double)data->tile;
	rect_y = (double)row * (double)data->tile;
	if (cx < rect_x)
		dx = rect_x;
	else if (cx > rect_x + (double)data->tile)
		dx = rect_x + (double)data->tile;
	else
		dx = cx;
	if (cy < rect_y)
		dy = rect_y;
	else if (cy > rect_y + (double)data->tile)
		dy = rect_y + (double)data->tile;
	else
		dy = cy;
	dx = cx - dx;
	dy = cy - dy;
	return (dx * dx + dy * dy <= 
		(double)data->player.radius * (double)data->player.radius);
}

static int	check_collision_range(t_cub3d *data, double cx, double cy, int start_row, int end_row)
{
	int	row;
	int	col;
	int	start_col;
	int	end_col;

	start_col = (int)floor((cx - data->player.radius) / (double)data->tile);
	end_col = floor((cx + data->player.radius) / (double)data->tile);
	if (start_col < 0)
		start_col = 0;
	if (end_col >= data->map.col_count)
		end_col = data->map.col_count - 1;
	
	// Performance optimization: early exit if no tiles to check
	if (start_row > end_row || start_col > end_col)
		return (0);

	row = start_row;
	while (row <= end_row)
	{
		col = start_col;
		while (col <= end_col)
		{
			// Check wall tile first (cheaper than intersection calc)
			if (data->map.grid[row][col] == '1')
			{
				if (circle_intersects_rectangle(data, cx, cy, row, col))
					return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}


int	circle_collides_wall(t_cub3d *data, double cx, double cy)
{
	int	start_row;
	int	end_row;

	// Early bounds checking optimization - avoid collision calculation if completely outside map
	if (cx + data->player.radius < 0 || 
		cx - data->player.radius >= data->map.col_count * data->tile ||
		cy + data->player.radius < 0 || 
		cy - data->player.radius >= data->map.row_count * data->tile)
		return (1); // Treat outside bounds as collision

	start_row = (int)floor((cy - data->player.radius) / (double)data->tile);
	end_row = (int)floor((cy + data->player.radius) / (double)data->tile);
	if (start_row < 0)
		start_row = 0;
	if (end_row >= data->map.row_count)
		end_row = data->map.row_count - 1;
	return (check_collision_range(data, cx, cy, start_row, end_row));
}


static void	calculate_movement_direction(t_cub3d *data, double *dx, double *dy)
{
	double forward_x, forward_y, right_x, right_y;
	
	// Get player's current direction (where the red line points)
	forward_x = data->player.dir_x;
	forward_y = data->player.dir_y;
	
	// Calculate perpendicular direction for strafing
	// Right vector is 90 degrees clockwise from forward
	right_x = forward_y;   // perpendicular right
	right_y = -forward_x;
	
	
	// Initialize movement
	*dx = 0.0;
	*dy = 0.0;

	// Forward/Backward movement (in direction of red line)
	if (data->keys.w)
	{
		*dx += forward_x;
		*dy += forward_y;
	}
	if (data->keys.s)
	{
		*dx -= forward_x;  // opposite direction
		*dy -= forward_y;
	}
	
	// Strafe left/right (perpendicular to red line)
	if (data->keys.a)
	{
		*dx += right_x;  // strafe left
		*dy += right_y;
	}
	if (data->keys.d)
	{
		*dx -= right_x;  // strafe right
		*dy -= right_y;
	}
	
	// Normalize diagonal movement
	if (*dx != 0.0 && *dy != 0.0)
	{
		*dx *= DIAGONAL_FACTOR;
		*dy *= DIAGONAL_FACTOR;
	}
}

static void	attempt_movement_with_collision(t_cub3d *data, double nx, double ny)
{
	if (!circle_collides_wall(data, nx, ny))
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
		return ;
	}
	if (!circle_collides_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	else if (!circle_collides_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	player_movement(t_cub3d *data, double dt)
{
	double	move_distance;
	double	new_x;
	double	new_y;
	double	direction_x;
	double	direction_y;
	double	current_speed;
	
	if (dt <= 0.0)
		return ;
	
	calculate_movement_direction(data, &direction_x, &direction_y);
	
	// Early exit optimization: no movement input detected
	if (direction_x == 0.0 && direction_y == 0.0)
		return ;
	
	// Apply sprint multiplier when Shift is held
	current_speed = data->player.speed;
	if (data->keys.shift)
		current_speed *= SPRINT_MULTIPLIER;
	
	move_distance = current_speed * dt;
	new_x = data->player.pos_x + direction_x * move_distance;
	new_y = data->player.pos_y + direction_y * move_distance;
	
	// Early bounds checking optimization: avoid collision calc if clearly outside map
	double map_width = data->map.col_count * data->tile;
	double map_height = data->map.row_count * data->tile;
	double radius = data->player.radius;
	
	// Clamp new position to stay within valid bounds (with radius buffer)
	if (new_x - radius < 0)
		new_x = radius;
	else if (new_x + radius > map_width)
		new_x = map_width - radius;
	
	if (new_y - radius < 0)
		new_y = radius;
	else if (new_y + radius > map_height)
		new_y = map_height - radius;

	attempt_movement_with_collision(data, new_x, new_y);
}

void	player_jump(t_cub3d *data, double dt)
{
	if (dt <= 0.0)
		return ;
	
	// Initiate jump if space pressed and player is on ground
	if (data->keys.space && !data->player.is_jumping && data->player.z_offset <= 0.0)
	{
		data->player.vertical_velocity = JUMP_VELOCITY;
		data->player.is_jumping = 1;
	}
	
	// Apply gravity to vertical velocity
	if (data->player.is_jumping || data->player.z_offset > 0.0)
	{
		data->player.vertical_velocity -= GRAVITY * dt;
		data->player.z_offset += data->player.vertical_velocity * dt;
		
		// Clamp to max jump height
		if (data->player.z_offset > MAX_JUMP_HEIGHT)
		{
			data->player.z_offset = MAX_JUMP_HEIGHT;
			data->player.vertical_velocity = 0.0;
		}
		
		// Land on ground
		if (data->player.z_offset <= 0.0)
		{
			data->player.z_offset = 0.0;
			data->player.vertical_velocity = 0.0;
			data->player.is_jumping = 0;
		}
	}
}

void	cycle_fov(t_cub3d *data)
{
	double	fov_value;
	double	plane_magnitude;
	double	old_plane_x;
	double	old_plane_y;
	
	// Calculate current plane magnitude to preserve direction
	old_plane_x = data->player.plane_x;
	old_plane_y = data->player.plane_y;
	plane_magnitude = sqrt(old_plane_x * old_plane_x + old_plane_y * old_plane_y);
	
	// If plane magnitude is zero, can't determine direction
	if (plane_magnitude < 0.001)
		return ;
	
	// Cycle to next FOV level: normal(0) -> narrow(1) -> wide(2) -> normal(0)
	data->player.fov_level = (data->player.fov_level + 1) % 3;
	// Get FOV value for current level
	if (data->player.fov_level == 0)
		fov_value = FOV_NORMAL;
	else if (data->player.fov_level == 1)
		fov_value = FOV_NARROW;
	else
		fov_value = FOV_WIDE;
	
	// Update plane vectors maintaining perpendicular direction
	// Normalize old plane and scale by new FOV
	data->player.plane_x = (old_plane_x / plane_magnitude) * fov_value;
	data->player.plane_y = (old_plane_y / plane_magnitude) * fov_value;
}
