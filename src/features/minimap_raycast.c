#include "cub3d.h"

/*
** Initializes ray calculation variables for DDA algorithm.
** Converts player position to grid coordinates and calculates delta distances.
** ray_dir[0] = ray_dx (ray direction X), ray_dir[1] = ray_dy (ray direction Y)
** dda_vars[0] = pos_x (player grid X), dda_vars[1] = pos_y (player grid Y)
** dda_vars[2] = delta_x (distance to cross one X grid)
** dda_vars[3] = delta_y (distance to cross one Y grid)
** dda_vars[4] = side_x (distance to next X boundary)
** dda_vars[5] = side_y (distance to next Y boundary)
** Process: Convert player pixel position to grid coordinates, then calculate
** delta distances representing how far ray travels to cross 1 grid square.
*/
static void	init_ray_calc(t_cub3d *data, double ray_dir[2], double dda_vars[6])
{
	dda_vars[0] = data->player.pos_x / data->tile;
	dda_vars[1] = data->player.pos_y / data->tile;
	if (ray_dir[0] == 0)
		dda_vars[2] = 1e30;
	else
		dda_vars[2] = fabs(1.0 / ray_dir[0]);
	if (ray_dir[1] == 0)
		dda_vars[3] = 1e30;
	else
		dda_vars[3] = fabs(1.0 / ray_dir[1]);
}

/*
** Calculates step direction and initial side distances for DDA.
** Determines whether to step in positive or negative direction for each axis.
** ray_dir[0] = ray_dx, ray_dir[1] = ray_dy
** dda_vars contains pos_x, pos_y, delta_x, delta_y, side_x, side_y
** step_dir[0] = step_x (-1 or +1), step_dir[1] = step_y (-1 or +1)
** Process: For X direction, determine step direction and calculate distance
** to first X boundary. Repeat for Y direction.
*/
static void	init_step_side(double ray_dir[2],
	double dda_vars[6], int step_dir[2])
{
	if (ray_dir[0] < 0)
	{
		step_dir[0] = -1;
		dda_vars[4] = (dda_vars[0] - (int)dda_vars[0]) * dda_vars[2];
	}
	else
	{
		step_dir[0] = 1;
		dda_vars[4] = ((int)dda_vars[0] + 1.0 - dda_vars[0]) * dda_vars[2];
	}
	if (ray_dir[1] < 0)
	{
		step_dir[1] = -1;
		dda_vars[5] = (dda_vars[1] - (int)dda_vars[1]) * dda_vars[3];
	}
	else
	{
		step_dir[1] = 1;
		dda_vars[5] = ((int)dda_vars[1] + 1.0 - dda_vars[1]) * dda_vars[3];
	}
}

/*
** Checks if the given map coordinates contain a wall or closed door.
** map_pos[0] = map_x (grid column), map_pos[1] = map_y (grid row)
** Returns 1 if there's a collision (wall '1' or closed door 'D'), 0 otherwise.
*/
static int	check_wall_hit(t_cub3d *data, int map_pos[2])
{
	if (data->map.grid[map_pos[1]][map_pos[0]] == '1')
		return (1);
	if (data->map.grid[map_pos[1]][map_pos[0]] == 'D'
		&& !is_door_open(data, map_pos[0], map_pos[1]))
		return (1);
	return (0);
}

/*
** Performs DDA (Digital Differential Analysis) to find wall distance.
** Steps through the grid until hitting a wall or map boundary.
** dda_vars[0-1] = pos_x/y, [2-3] = delta_x/y, [4-5] = side_x/y
** step_dir[0] = step_x, step_dir[1] = step_y
** Returns the distance traveled when hitting a wall.
** Process: Start at current grid position, then repeatedly jump to the next
** closest grid line (X or Y side). Check bounds and walls at each step.
*/
static double	perform_minimap_dda(t_cub3d *data,
	double dda_vars[6], int step_dir[2])
{
	int	map_pos[2];

	map_pos[0] = (int)dda_vars[0];
	map_pos[1] = (int)dda_vars[1];
	while (1)
	{
		if (dda_vars[4] < dda_vars[5])
		{
			map_pos[0] += step_dir[0];
			if (map_pos[0] < 0 || map_pos[0] >= data->map.col_count)
				return (dda_vars[4]);
			if (check_wall_hit(data, map_pos))
				return (dda_vars[4]);
			dda_vars[4] += dda_vars[2];
		}
		else
		{
			map_pos[1] += step_dir[1];
			if (map_pos[1] < 0 || map_pos[1] >= data->map.row_count)
				return (dda_vars[5]);
			if (check_wall_hit(data, map_pos))
				return (dda_vars[5]);
			dda_vars[5] += dda_vars[3];
		}
	}
}

/*
** Calculates the distance from player to nearest wall in given direction.
** Uses DDA algorithm to trace ray through the map grid.
** ray_dx = ray direction X component, ray_dy = ray direction Y component
** Returns the perpendicular distance to the wall hit.
** Process: Store ray direction, initialize DDA variables and step direction,
** then perform DDA and return wall distance.
*/
double	minimap_ray_dist(t_cub3d *data, double ray_dx, double ray_dy)
{
	double	ray_dir[2];
	double	dda_vars[6];
	int		step_dir[2];

	ray_dir[0] = ray_dx;
	ray_dir[1] = ray_dy;
	init_ray_calc(data, ray_dir, dda_vars);
	init_step_side(ray_dir, dda_vars, step_dir);
	return (perform_minimap_dda(data, dda_vars, step_dir));
}
