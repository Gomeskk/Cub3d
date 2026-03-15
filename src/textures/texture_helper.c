
#include "cub3d.h"


// Get pixel color from texture at coordinates (x, y)
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;
	int		row_offset;
	int		col_offset;
	int		bytes_per_pixel;

	// Bounds check to prevent segfault
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
	// Calculate pixel address in texture data
	bytes_per_pixel = texture->bpp / 8;
	row_offset = y * texture->size_line;
	col_offset = x * bytes_per_pixel;
	pixel = texture->data + row_offset + col_offset;
	return (*(unsigned int *)pixel);
}

/*
** Calculate texture X coordinate from wall hit position
** wall_x is fractional part (0.0 to 1.0) of where wall was hit
** Flip texture horizontally for certain wall orientations
** to ensure correct appearance from all viewing angles
*/
int	get_tex_x(t_img *texture, double wall_x, t_ray *ray)
{
	int		tex_x;
	int		is_west_wall;
	int		is_south_wall;
	int		needs_mirror;

	// Map wall_x (0.0-1.0) to texture pixel coordinate
	tex_x = (int)(wall_x * (double)texture->width);
	// Check which wall orientation we're viewing
	is_west_wall = (ray->side == 0 && ray->ray_dir_x > 0);
	is_south_wall = (ray->side == 1 && ray->ray_dir_y < 0);
	needs_mirror = is_west_wall || is_south_wall;
	// Mirror texture for certain wall sides to maintain correct orientation
	if (needs_mirror)
		tex_x = texture->width - tex_x - 1;
	// Clamp to valid texture bounds
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

/*
** Initialize texture stepping values for vertical column rendering
** step: how much to advance in texture per screen pixel
** tex_pos: starting Y position in texture (accounting for pitch/jump)
** Adjusts for player pitch (looking up/down) and z_offset (jumping)
*/
void	init_texture_step(t_img *texture, t_ray *ray,
			t_cub3d *data, t_tex_draw *td)
{
	int	screen_y;
	int	wall_center_offset;

	// Calculate step size: texture pixels per screen pixel
	td->step = (double)texture->height / (double)ray->line_height;
	// Start from top of wall slice on screen
	screen_y = ray->draw_start;
	// Adjust for looking up/down (pitch) and jumping (z_offset)
	screen_y -= (int)data->player.pitch;
	screen_y -= (int)data->player.z_offset;
	// Adjust for vertical position: shift based on wall size vs screen size
	// This accounts for walls taller/shorter than screen height
	wall_center_offset = ray->line_height / 2 - data->current_height / 2;
	screen_y += wall_center_offset;
	// Convert screen position to texture position
	td->tex_pos = screen_y * td->step;
}

// Draw one vertical column of textured wall
void	draw_texture_column(t_cub3d *data, t_tex_draw *td,
			t_img *texture, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = td->ray->draw_start;
	while (y < td->ray->draw_end)
	{
		// Get current texture Y coordinate (may exceed texture bounds)
		tex_y = (int)td->tex_pos;
		// TEXTURE WRAPPING FIX: Use modulo for any texture height
		// Previous bitwise AND (&) only worked for power-of-2 heights
		tex_y = tex_y % texture->height;
		// Handle negative values from pitch/jump offset (wrap to positive)
		if (tex_y < 0)
			tex_y += texture->height;
		// Get texture color and draw to screen
		color = get_texture_pixel(texture, td->tex_x, tex_y);
		pixel_put(&data->img, x, y, color);
		// Move down in texture for next screen pixel
		td->tex_pos += td->step;
		y++;
	}
}
