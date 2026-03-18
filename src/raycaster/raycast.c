/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:12:53 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 01:02:40 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_wall_draw_bounds(t_cub3d *data, t_ray *ray)
{
	double	plane_mag;
	int		vertical_offset;

	plane_mag = sqrt(data->player.plane_x * data->player.plane_x
			+ data->player.plane_y * data->player.plane_y);
	ray->line_height = (int)(data->current_height
			/ ray->perp_wall_dist * (FOV_NORMAL / plane_mag));
	vertical_offset = (int)data->player.pitch + (int)data->player.z_offset;
	ray->draw_start = -ray->line_height / 2
		+ data->current_height / 2 + vertical_offset;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2
		+ data->current_height / 2 + vertical_offset;
	if (ray->draw_end >= data->current_height)
		ray->draw_end = data->current_height - 1;
}

static void	draw_column_ceiling(t_cub3d *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		pixel_put(&data->img, x, y, data->textures.ceiling);
		y++;
	}
}

static void	draw_column_floor(t_cub3d *data, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < data->current_height)
	{
		pixel_put(&data->img, x, y, data->textures.floor);
		y++;
	}
}

void	draw_wall_column(t_cub3d *data, t_ray *ray, int x)
{
	set_wall_draw_bounds(data, ray);
	draw_column_ceiling(data, ray, x);
	draw_textured_wall(data, ray, x);
	draw_column_floor(data, ray, x);
}

void	raycast_render(t_cub3d *data)
{
	int	x;

	clear_image(&data->img, 0x000000);
	x = 0;
	while (x < data->current_width)
	{
		init_ray(data, &data->ray, x);
		perform_dda(data, &data->ray);
		draw_wall_column(data, &data->ray, x);
		if (data->z_buffer)
			data->z_buffer[x] = data->ray.perp_wall_dist;
		x++;
	}
	render_enemies(data);
	apply_flashlight(data);
}
