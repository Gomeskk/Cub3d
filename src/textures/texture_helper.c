/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:25:15 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/19 01:25:16 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns the pixel color at (x, y) inside a texture image buffer.
** If coordinates are outside bounds, returns black to avoid invalid access.
*/
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;
	int		row_offset;
	int		col_offset;
	int		bytes_per_pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x000000);
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
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->step_x < 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->step_y > 0)
		tex_x = texture->width - tex_x - 1;
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

	td->step = (double)texture->height / (double)ray->line_height;
	screen_y = ray->draw_start;
	screen_y -= (int)data->player.pitch;
	screen_y -= (int)data->player.z_offset;
	wall_center_offset = ray->line_height / 2 - data->current_height / 2;
	screen_y += wall_center_offset;
	td->tex_pos = screen_y * td->step;
}

void	fill_wall_images(t_cub3d *data, void **images)
{
	images[0] = data->wall_textures.north.image;
	images[1] = data->wall_textures.south.image;
	images[2] = data->wall_textures.east.image;
	images[3] = data->wall_textures.west.image;
	images[4] = data->wall_textures.door.image;
	images[5] = data->wall_textures.button.image;
	images[6] = data->wall_textures.alt_button.image;
	images[7] = data->wall_textures.alt_north.image;
	images[8] = data->wall_textures.alt_south.image;
	images[9] = data->wall_textures.alt_east.image;
	images[10] = data->wall_textures.alt_west.image;
}

/*
** Draws one vertical wall column using current texture sampling state.
** Wraps tex_y with modulo so any texture height is supported.
** Handles negative tex_y values caused by camera pitch/jump offsets.
*/
void	draw_texture_column(t_cub3d *data, t_tex_draw *td,
			t_img *texture, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = td->ray->draw_start;
	while (y < td->ray->draw_end)
	{
		tex_y = (int)td->tex_pos;
		tex_y = tex_y % texture->height;
		if (tex_y < 0)
			tex_y += texture->height;
		color = get_texture_pixel(texture, td->tex_x, tex_y);
		pixel_put(&data->img, x, y, color);
		td->tex_pos += td->step;
		y++;
	}
}
