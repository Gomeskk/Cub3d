#include "cub3d.h"

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
void	draw_player_on_map(t_cub3d *data, int params[3])
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
	put_player_dot(&data->img, player_pos[0], player_pos[1], 0xfc03d2);
}
