
#include "cub3d.h"

// Initialize buttons array and count them in the map
void	init_buttons(t_cub3d *data)
{
	int	y;
	int	x;

	data->map.button_count = 0;
	y = 0;
	// First pass: count all buttons in the map
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'B')
				data->map.button_count++;
			x++;
		}
		y++;
	}
	// No buttons found, nothing to allocate
	if (data->map.button_count == 0)
	{
		data->map.buttons = NULL;
		return ;
	}
	// Allocate memory for all buttons found
	data->map.buttons = malloc(sizeof(t_button) * data->map.button_count);
}

// Store button positions and initialize them as not activated
void	store_button_positions(t_cub3d *data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	// Second pass: store each button's position
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'B')
			{
				// Store grid coordinates
				data->map.buttons[i].x = x;
				data->map.buttons[i].y = y;
				// Initialize as not activated
				data->map.buttons[i].is_activated = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

// Check if button is at given grid position
int	is_button(t_cub3d *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.button_count)
	{
		// Find button at this position
		if (data->map.buttons[i].x == x && data->map.buttons[i].y == y)
			return (1);
		i++;
	}
	// Button not found at this position
	return (0);
}

// Swap all wall textures to alternate texture
static void	swap_to_alternate(t_cub3d *data)
{
	t_wall_textures	*wt;
	t_img			temp;

	wt = &data->wall_textures;
	// Store the alternate texture (Wall_W.xpm)
	temp = wt->alt_north;
	// Save original textures to alt slots for potential restore
	wt->alt_north = wt->north;
	wt->alt_south = wt->south;
	wt->alt_east = wt->east;
	wt->alt_west = wt->west;
	// Set all directions to use the alternate texture
	wt->north = temp;
	wt->south = temp;
	wt->east = temp;
	wt->west = temp;
	// Change button texture to show it's been activated
	wt->button = temp;
	wt->textures_swapped = 1;
}

// Activate button if player is close enough
void	activate_button(t_cub3d *data)
{
	int		grid_x;
	int		grid_y;
	int		i;
	double	dist;

	// Get player's current grid position
	grid_x = (int)(data->player.pos_x / data->tile);
	grid_y = (int)(data->player.pos_y / data->tile);
	i = 0;
	// Check all buttons for proximity to player
	while (i < data->map.button_count)
	{
		// Calculate distance from player to button
		dist = sqrt(pow(data->map.buttons[i].x - grid_x, 2)
				+ pow(data->map.buttons[i].y - grid_y, 2));
		// Button is within interaction range and not yet activated
		if (dist < 1.5 && !data->map.buttons[i].is_activated)
		{
			// Mark button as activated
			data->map.buttons[i].is_activated = 1;
			// Swap all textures to alternate
			swap_to_alternate(data);
			return ;
		}
		i++;
	}
}
