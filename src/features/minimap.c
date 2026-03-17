
#include "cub3d.h"

/*
** Returns the color for a specific map tile based on its type.
** Walls are cyan, doors are purple (green if open), buttons are yellow.
*/
static int	get_tile_color(t_cub3d *data, int x, int y)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == '1')
		return (0x00FFFF);
	else if (tile == 'D')
	{
		if (is_door_open(data, x, y))
			return (0x00FF00);
		else
			return (0x8704E4);
	}
	else if (tile == 'B')
		return (0xFFFF00);
	else if (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W')
		return (0x000000);
	return (0x000000);
}

/*
** Draws a single tile on the minimap at the given grid position.
** Skips empty spaces and calculates screen position from params.
** params[0] = tile_size (pixels per tile)
** params[1] = offset (margin from screen edge)
*/
static void	draw_map_tile(t_cub3d *data, int x, int y, int params[2])
{
	int		screen_x;
	int		screen_y;
	int		color;
	char	tile;

	tile = data->map.grid[y][x];
	if (tile == ' ' || tile == '\0')
		return ;
	screen_x = params[1] + x * params[0];
	screen_y = params[1] + y * params[0];
	color = get_tile_color(data, x, y);
	put_color_tile(&data->img, screen_x, screen_y, color, params[0]);
}

/*
** Iterates through the entire map grid and draws each tile.
** params[0] = tile size, params[1] = offset from screen edge.
*/
static void	draw_map_tiles(t_cub3d *data, int params[2])
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.row_count)
	{
		x = 0;
		while (x < data->map.col_count && data->map.grid[y][x])
		{
			draw_map_tile(data, x, y, params);
			x++;
		}
		y++;
	}
}

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
static double	perform_dda(t_cub3d *data, double dda_vars[6], int step_dir[2])
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
static double	minimap_ray_dist(t_cub3d *data, double ray_dx, double ray_dy)
{
	double	ray_dir[2];
	double	dda_vars[6];
	int		step_dir[2];

	ray_dir[0] = ray_dx;
	ray_dir[1] = ray_dy;
	init_ray_calc(data, ray_dir, dda_vars);
	init_step_side(ray_dir, dda_vars, step_dir);
	return (perform_dda(data, dda_vars, step_dir));
}

/*
** Draws a line on the minimap using Bresenham-like algorithm.
** line_coords[0] = start_x, [1] = start_y, [2] = end_x, [3] = end_y
** color = RGB hex color value for the line
** Process: Calculate number of steps needed (larger of dx or dy), calculate
** increment per step for smooth line, then draw each pixel along the line.
*/
static void	draw_minimap_line(t_img *img, int line_coords[4], int color)
{
	int		total_steps;
	double	step_x;
	double	step_y;
	int		i;

	total_steps = abs(line_coords[2] - line_coords[0]);
	if (abs(line_coords[3] - line_coords[1]) > total_steps)
		total_steps = abs(line_coords[3] - line_coords[1]);
	if (total_steps == 0)
		return ;
	step_x = (double)(line_coords[2] - line_coords[0]) / total_steps;
	step_y = (double)(line_coords[3] - line_coords[1]) / total_steps;
	i = -1;
	while (++i <= total_steps)
		pixel_put(img, line_coords[0] + (int)(step_x * i),
			line_coords[1] + (int)(step_y * i), color);
}

/*
** Wrapper function to draw a single ray line from player to hit point.
** player_pos[0] = player screen X, player_pos[1] = player screen Y
** hit_pos[0] = wall hit screen X, hit_pos[1] = wall hit screen Y
** Process: Build coordinate array from start point (player) to end point
** (wall hit), then draw the ray line in purple color (0xdb6cea).
*/
static void	draw_ray_line(t_cub3d *data, int player_pos[2], int hit_pos[2])
{
	int	line_coords[4];

	line_coords[0] = player_pos[0];
	line_coords[1] = player_pos[1];
	line_coords[2] = hit_pos[0];
	line_coords[3] = hit_pos[1];
	draw_minimap_line(&data->img, line_coords, 0xdb6cea);
}

/*
** Casts a single ray from player position for minimap FOV cone.
** Calculates ray direction, distance to wall, and draws the ray.
** params[2] = map_scale_x1000, player_pos = screen coordinates
** ray_index = which ray in the FOV (0-60)
** Process: Calculate camera X position (-1 to +1 across screen), calculate
** ray direction using player direction + camera plane, find distance to wall,
** calculate hit position on screen (convert to minimap scale), then draw ray.
*/
static void	cast_minimap_ray(t_cub3d *data, int params[3],
	int player_pos[2], int ray_index)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_dist;
	int		hit_pos[2];

	camera_x = 2.0 * ray_index / 60.0 - 1.0;
	ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
	wall_dist = minimap_ray_dist(data, ray_dir_x, ray_dir_y);
	hit_pos[0] = player_pos[0] + (int)(ray_dir_x * wall_dist
			* data->tile * params[2] / 1000.0);
	hit_pos[1] = player_pos[1] + (int)(ray_dir_y * wall_dist
			* data->tile * params[2] / 1000.0);
	draw_ray_line(data, player_pos, hit_pos);
}

/*
** Draws the player on the minimap with a FOV cone showing vision.
** Casts 60 rays to create the field of view visualization.
** params[1] = offset, params[2] = map_scale_x1000
** Process: Convert player world position to minimap screen position, cast
** 60 rays to create FOV cone visualization, then draw player dot in pink
** color (0xfc03d2) with radius 3.
*/
static void	draw_player_on_map(t_cub3d *data, int params[3])
{
	int		player_pos[2];
	int		num_rays;
	int		ray_index;

	player_pos[0] = params[1] + (int)(data->player.pos_x * params[2] / 1000.0);
	player_pos[1] = params[1] + (int)(data->player.pos_y * params[2] / 1000.0);
	num_rays = 60;
	ray_index = -1;
	while (++ray_index <= num_rays)
		cast_minimap_ray(data, params, player_pos, ray_index);
	put_player_dot(&data->img, player_pos[0], player_pos[1], 3, 0xfc03d2);
}

/*
** Draws a circle outline representing an enemy's vision radius.
** Uses 360 angle steps to create a smooth circular outline.
** enemy_x/enemy_y = enemy center position on screen (in pixels)
** radius_px = vision radius in pixels
** Process: Draw circle by calculating points at each degree (0-359), convert
** degrees to radians for trigonometric functions, calculate point on circle
** using cos/sin, then draw pixel if within screen bounds.
*/
static void	draw_enemy_vision(t_cub3d *data, int enemy_x, int enemy_y,
	int radius_px)
{
	int		angle_deg;
	double	angle_rad;
	int		circle_x;
	int		circle_y;

	angle_deg = 0;
	while (angle_deg < 360)
	{
		angle_rad = angle_deg * M_PI / 180.0;
		circle_x = enemy_x + (int)(cos(angle_rad) * radius_px);
		circle_y = enemy_y + (int)(sin(angle_rad) * radius_px);
		if (circle_x >= 0 && circle_x < data->current_width
			&& circle_y >= 0 && circle_y < data->current_height)
			pixel_put(&data->img, circle_x, circle_y, 0xFF0000);
		angle_deg++;
	}
}

/*
** Draws a single enemy on the minimap with vision radius circle.
** Calculates enemy screen position and displays with yellow dot.
** params[1] = offset, params[2] = map_scale_x1000
** enemy_index = which enemy in the enemies array to draw
** Process: Convert enemy world position to minimap screen position, convert
** vision radius from grid units to screen pixels, draw red circle showing
** vision radius, then draw yellow dot at enemy position (0xFCF803).
*/
static void	draw_enemy_on_map(t_cub3d *data, int params[3], int enemy_index)
{
	int	enemy_screen_x;
	int	enemy_screen_y;
	int	vision_radius_px;

	enemy_screen_x = params[1] + (int)(data->map.enemies[enemy_index].pos_x
			* params[2] / 1000.0);
	enemy_screen_y = params[1] + (int)(data->map.enemies[enemy_index].pos_y
			* params[2] / 1000.0);
	vision_radius_px = (int)(data->map.enemies[enemy_index].vision_radius
			* data->tile * params[2] / 1000.0);
	draw_enemy_vision(data, enemy_screen_x, enemy_screen_y, vision_radius_px);
	put_player_dot(&data->img, enemy_screen_x, enemy_screen_y, 3, 0xFCF803);
}

/*
** Iterates through all enemies and draws them on the minimap.
** Each enemy is shown with vision radius and position marker.
** params contains minimap scaling and offset information.
** Process: Loop through all enemies in the map and draw each one.
*/
static void	draw_enemies_on_map(t_cub3d *data, int params[3])
{
	int	enemy_index;

	enemy_index = 0;
	while (enemy_index < data->map.enemy_count)
	{
		draw_enemy_on_map(data, params, enemy_index);
		enemy_index++;
	}
}

/*
** Main function to render the complete minimap display.
** Calculates scaling, draws map tiles, enemies, and player FOV cone.
** Minimap size adapts to screen width, minimum 5 pixels per tile.
** Process: Calculate tile size based on screen width (responsive minimap),
** calculate offset/margin from screen edge, set player FOV line length
** slightly larger than tiles, calculate scale factor (multiply by 1000 to
** avoid floating point), pack parameters [0]=tile_size, [1]=offset,
** [2]=scale*1000, draw all map tiles (walls, doors, floors), draw all
** enemies with vision circles, update params for player rendering (use longer
** lines for FOV), then draw player position and FOV cone.
*/
void	render_minimap(t_cub3d *data)
{
	int		tile_size;
	int		screen_offset;
	int		player_line_len;
	int		render_params[3];
	double	map_scale;

	tile_size = data->current_width / 128;
	if (tile_size < 5)
		tile_size = 5;
	screen_offset = data->current_width / 160;
	if (screen_offset < 5)
		screen_offset = 5;
	player_line_len = tile_size + 3;
	map_scale = (double)tile_size / data->tile;
	render_params[0] = tile_size;
	render_params[1] = screen_offset;
	render_params[2] = (int)(map_scale * 1000);
	draw_map_tiles(data, render_params);
	draw_enemies_on_map(data, render_params);
	render_params[0] = player_line_len;
	draw_player_on_map(data, render_params);
}
