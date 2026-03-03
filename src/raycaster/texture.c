/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:00:00 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/03 16:51:17 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Load all wall textures
int	load_wall_textures(t_cub3d *data)
{
	data->wall_textures.north.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Walls/Wall_N.xpm",
		&data->wall_textures.north.width,
		&data->wall_textures.north.height);
	if (!data->wall_textures.north.image)
		return (0);
	data->wall_textures.north.data = mlx_get_data_addr(
		data->wall_textures.north.image,
		&data->wall_textures.north.bpp,
		&data->wall_textures.north.size_line,
		&data->wall_textures.north.type);
	
	data->wall_textures.south.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Walls/Wall_S.xpm",
		&data->wall_textures.south.width,
		&data->wall_textures.south.height);
	if (!data->wall_textures.south.image)
		return (0);
	data->wall_textures.south.data = mlx_get_data_addr(
		data->wall_textures.south.image,
		&data->wall_textures.south.bpp,
		&data->wall_textures.south.size_line,
		&data->wall_textures.south.type);
	
	data->wall_textures.east.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Walls/Wall_E.xpm",
		&data->wall_textures.east.width,
		&data->wall_textures.east.height);
	if (!data->wall_textures.east.image)
		return (0);
	data->wall_textures.east.data = mlx_get_data_addr(
		data->wall_textures.east.image,
		&data->wall_textures.east.bpp,
		&data->wall_textures.east.size_line,
		&data->wall_textures.east.type);
	
	data->wall_textures.west.image = mlx_xpm_file_to_image(data->mlx,
		"Png_images/Walls/Wall_W.xpm",
		&data->wall_textures.west.width,
		&data->wall_textures.west.height);
	if (!data->wall_textures.west.image)
		return (0);
	data->wall_textures.west.data = mlx_get_data_addr(
		data->wall_textures.west.image,
		&data->wall_textures.west.bpp,
		&data->wall_textures.west.size_line,
		&data->wall_textures.west.type);
	
	return (1);
}

// Get pixel color from texture
static int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;
	
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	
	pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

// Select the appropriate texture based on wall direction
static t_img	*select_wall_texture(t_cub3d *data, t_ray *ray)
{
	if (ray->side == 0)  // X-side hit (vertical walls)
	{
		if (ray->step_x > 0)  // Moving east, hit west face
			return (&data->wall_textures.west);
		else  // Moving west, hit east face
			return (&data->wall_textures.east);
	}
	else  // Y-side hit (horizontal walls)
	{
		if (ray->step_y > 0)  // Moving south, hit north face
			return (&data->wall_textures.north);
		else  // Moving north, hit south face
			return (&data->wall_textures.south);
	}
}

// Calculate the X coordinate on the texture
static double	calculate_wall_x(t_cub3d *data, t_ray *ray)
{
	double	wall_x;
	
	if (ray->side == 0)  // X-side hit
		wall_x = data->player.pos_y / data->tile + ray->perp_wall_dist * ray->ray_dir_y;
	else  // Y-side hit
		wall_x = data->player.pos_x / data->tile + ray->perp_wall_dist * ray->ray_dir_x;
	
	wall_x -= floor(wall_x);  // Get fractional part
	return (wall_x);
}

// Main texture rendering function - called for each wall column
void	draw_textured_wall(t_cub3d *data, t_ray *ray, int x)
{
	t_img	*texture;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
	int		y;
	
	// Select the appropriate texture
	texture = select_wall_texture(data, ray);
	
	// Calculate wall_x (where exactly the wall was hit)
	wall_x = calculate_wall_x(data, ray);
	
	// X coordinate on the texture
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || 
		(ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	
	// Calculate step and starting position for texture
	step = (double)texture->height / (double)ray->line_height;
	tex_pos = (ray->draw_start - (int)data->player.pitch - (int)data->player.z_offset 
				- data->current_height / 2 + ray->line_height / 2) * step;
	
	// Draw the textured wall column
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_texture_pixel(texture, tex_x, tex_y);
		pixel_put(&data->img, x, y, color);
		y++;
	}
}
