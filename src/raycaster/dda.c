#include "cub3d.h"

void	setup_dda(t_cub3d *data, t_ray *ray)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player.pos_x / data->tile;
	pos_y = data->player.pos_y / data->tile;
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

static int	update_dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	return (0);
}

static int	check_dda_hit(t_cub3d *data, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= data->map.col_count
		|| ray->map_y < 0 || ray->map_y >= data->map.row_count)
	{
		ray->hit = 1;
		return (1);
	}
	if (data->map.grid[ray->map_y][ray->map_x] == '1')
		ray->hit = 1;
	if (data->map.grid[ray->map_y][ray->map_x] == 'D')
	{
		if (!is_door_open(data, ray->map_x, ray->map_y))
		{
			ray->hit = 1;
			ray->hit_door = 1;
		}
	}
	if (data->map.grid[ray->map_y][ray->map_x] == 'B')
	{
		ray->hit = 1;
		ray->hit_button = 1;
	}
	return (ray->hit);
}

static void	set_perp_wall_dist(t_cub3d *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - (data->player.pos_x / data->tile)
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - (data->player.pos_y / data->tile)
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void	perform_dda(t_cub3d *data, t_ray *ray)
{
	setup_dda(data, ray);
	while (ray->hit == 0)
	{
		update_dda_step(ray);
		if (check_dda_hit(data, ray))
			break ;
	}
	set_perp_wall_dist(data, ray);
}
