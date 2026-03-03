
#include "cub3d.h"

// Get pixel color from texture
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

// Calculate texture X coordinate and clamp to valid range
int	get_tex_x(t_img *texture, double wall_x, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

// Initialize texture step and starting position for column rendering
void	init_texture_step(t_img *texture, t_ray *ray,
			t_cub3d *data, t_tex_draw *td)
{
	td->step = (double)texture->height / (double)ray->line_height;
	td->tex_pos = (ray->draw_start - (int)data->player.pitch
			- (int)data->player.z_offset - data->current_height / 2
			+ ray->line_height / 2) * td->step;
}

// Draw one column of textured wall
void	draw_texture_column(t_cub3d *data, t_tex_draw *td,
			t_img *texture, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = td->ray->draw_start;
	while (y < td->ray->draw_end)
	{
		// Use modulo instead of bitwise AND to properly wrap texture coords
		tex_y = (int)td->tex_pos % texture->height;
		if (tex_y < 0)
			tex_y += texture->height;
		td->tex_pos += td->step;
		color = get_texture_pixel(texture, td->tex_x, tex_y);
		pixel_put(&data->img, x, y, color);
		y++;
	}
}
