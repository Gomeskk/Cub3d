
#include "cub3d.h"

// Helper function to load a single texture
static int	load_single_texture(void *mlx, t_img *tex, char *path)
{
	tex->image = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->image)
		return (0);
	tex->data = mlx_get_data_addr(tex->image, &tex->bpp,
			&tex->size_line, &tex->type);
	return (1);
}

// Load all wall textures including door texture
int	load_wall_textures(t_cub3d *data)
{
	if (!load_single_texture(data->mlx, &data->wall_textures.north,
			"Png_images/Walls/Wall_N.xpm"))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.south,
			"Png_images/Walls/Wall_S.xpm"))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.east,
			"Png_images/Walls/Wall_E.xpm"))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.west,
			"Png_images/Walls/Wall_W.xpm"))
		return (0);
	if (!load_single_texture(data->mlx, &data->wall_textures.door,
			"Png_images/Walls/Door.xpm"))
		return (0);
	return (1);
}

// Select the appropriate texture based on wall direction
static t_img	*select_wall_texture(t_cub3d *data, t_ray *ray)
{
	// DOOR CHECK: If ray hit a door, use door texture regardless of direction
	if (ray->hit_door)
		return (&data->wall_textures.door);
	
	// Determine wall orientation for texture selection
	if (ray->side == 0)	// Vertical wall (X-side hit)
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

// Calculate the X coordinate on the texture
static double	calculate_wall_x(t_cub3d *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)	// X-side hit (vertical wall)
		wall_x = data->player.pos_y / data->tile + ray->perp_wall_dist * ray->ray_dir_y;
	else	// Y-side hit (horizontal wall)
		wall_x = data->player.pos_x / data->tile + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);	// Get fractional part (0.0 to 1.0)
	return (wall_x);
}

// Main texture rendering function - called for each wall column
void	draw_textured_wall(t_cub3d *data, t_ray *ray, int x)
{
	t_img		*texture;
	t_tex_draw	td;

	// Select the appropriate texture
	texture = select_wall_texture(data, ray);
	td.ray = ray;
	// Calculate wall_x (where exactly the wall was hit)
	// X coordinate on the texture with bounds checking
	td.tex_x = get_tex_x(texture, calculate_wall_x(data, ray), ray);
	// Calculate step and starting position for texture
	init_texture_step(texture, ray, data, &td);
	// Draw the textured wall column
	draw_texture_column(data, &td, texture, x);
}
