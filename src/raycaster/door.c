
#include "cub3d.h"

// Initialize doors array and count them in the map
void	init_doors(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.door_count = 0;
	y = 0;
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
	if (data->map.door_count == 0)
	{
		data->map.doors = NULL;
		return ;
	}
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
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'D')
			{
				data->map.doors[i].x = x;
				data->map.doors[i].y = y;
				data->map.doors[i].is_open = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

// Check if door is open at given position
int	is_door_open(t_cub3d *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (data->map.doors[i].is_open);
		i++;
	}
	return (0);
}

// Toggle door state if player is close enough
void	toggle_door(t_cub3d *data)
{
	int		grid_x;
	int		grid_y;
	int		i;
	double	dist;

	grid_x = (int)(data->player.pos_x / data->tile);
	grid_y = (int)(data->player.pos_y / data->tile);
	i = 0;
	while (i < data->map.door_count)
	{
		dist = sqrt(pow(data->map.doors[i].x - grid_x, 2)
				+ pow(data->map.doors[i].y - grid_y, 2));
		if (dist < 1.5)
		{
			data->map.doors[i].is_open = !data->map.doors[i].is_open;
			return ;
		}
		i++;
	}
}
