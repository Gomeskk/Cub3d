/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:25:22 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/19 01:25:23 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Loads one XPM file into a texture struct.
** On success, fills image pointer, dimensions, and pixel buffer metadata.
** Returns 1 on success and 0 if image creation fails.
*/
static int	load_single_texture(void *mlx, t_img *tex, char *path)
{
	tex->image = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->image)
		return (0);
	tex->data = mlx_get_data_addr(tex->image, &tex->bpp,
			&tex->size_line, &tex->type);
	return (1);
}

int	load_wall_textures(t_cub3d *data)
{
	if (!load_single_texture(data->mlx, &data->wall_textures.north,
			data->textures.no))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.south,
			data->textures.so))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.east,
			data->textures.ea))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.west,
			data->textures.we))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.door,
			"Png_images/Walls/Door.xpm"))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.button,
			"Png_images/Walls/Button.xpm"))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.alt_north,
			data->textures.we))
		return (0);
	data->wall_textures.textures_swapped = 0;
	return (1);
}

/*
** Chooses which texture must be used for the current ray hit.
** Hit priority is: button first, then door, then directional wall texture.
** For normal walls, side and ray step decide the facing texture.
*/
static t_img	*select_wall_texture(t_cub3d *data, t_ray *ray)
{
	if (ray->hit_button)
		return (&data->wall_textures.button);
	if (ray->hit_door)
		return (&data->wall_textures.door);
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&data->wall_textures.west);
		else
			return (&data->wall_textures.east);
	}
	else
	{
		if (ray->step_y > 0)
			return (&data->wall_textures.north);
		else
			return (&data->wall_textures.south);
	}
}

/*
** Computes the horizontal hit position on the wall face in [0.0, 1.0).
** The axis used depends on whether the ray hit an X-side or Y-side wall.
** The fractional part is later converted into the texture X coordinate.
*/
static double	calculate_wall_x(t_cub3d *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->player.pos_y / data->tile
			+ ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player.pos_x / data->tile
			+ ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

/*
** Renders one textured screen column for the current ray.
** Selects texture, computes tex_x from hit position, initializes stepping,
** then draws the vertical textured column at screen coordinate x.
*/
void	draw_textured_wall(t_cub3d *data, t_ray *ray, int x)
{
	t_img		*texture;
	t_tex_draw	td;

	texture = select_wall_texture(data, ray);
	td.ray = ray;
	td.tex_x = get_tex_x(texture, calculate_wall_x(data, ray), ray);
	init_texture_step(texture, ray, data, &td);
	draw_texture_column(data, &td, texture, x);
}
