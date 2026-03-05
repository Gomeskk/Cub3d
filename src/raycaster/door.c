
#include "cub3d.h"

// Initialize doors array and count them in the map
void	init_doors(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.door_count = 0;
	y = 0;
	// First pass: count all doors in the map
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'D')
				data->map.door_count++;
			x++;
		}
		y++;
	}
	// No doors found, nothing to allocate
	if (data->map.door_count == 0)
	{
		data->map.doors = NULL;
		return ;
	}
	// Allocate memory for all doors found
	data->map.doors = malloc(sizeof(t_door) * data->map.door_count);
}

// Store door positions and initialize them as closed
void	store_door_positions(t_cub3d *data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	// Second pass: store each door's position
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'D')
			{
				// Store grid coordinates
				data->map.doors[i].x = x;
				data->map.doors[i].y = y;
				// Initialize as closed
				data->map.doors[i].is_open = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

// Check if door is open at given grid position
int	is_door_open(t_cub3d *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		// Find door at this position
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (data->map.doors[i].is_open);
		i++;
	}
	// Door not found at this position
	return (0);
}

// Toggle door state if player is close enough
void	toggle_door(t_cub3d *data)
{
	int		grid_x;
	int		grid_y;
	int		i;
	double	dist;

	// Get player's current grid position
	grid_x = (int)(data->player.pos_x / data->tile);
	grid_y = (int)(data->player.pos_y / data->tile);
	i = 0;
	// Check all doors for proximity to player
	while (i < data->map.door_count)
	{
		// Calculate Euclidean distance from player to door
		dist = sqrt(pow(data->map.doors[i].x - grid_x, 2)
				+ pow(data->map.doors[i].y - grid_y, 2));
		// Door is within interaction range (1.5 tiles)
		if (dist < 1.5)
		{
			// Toggle door state (open -> closed, closed -> open)
			data->map.doors[i].is_open = !data->map.doors[i].is_open;
			return ;
		}
		i++;
	}
}
