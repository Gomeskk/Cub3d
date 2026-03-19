/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:56:43 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/19 20:59:04 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Retrieves the current texture to use for rendering an enemy, 
//based on animation settings and frame count.
static t_img	*get_current_enemy_texture(t_cub3d *data)
{
	int		frame;
	double	t;

	if (!data->enemy_anim_enabled || data->enemy_frame_count <= 0)
		return (&data->enemy_texture);
	t = get_time_in_seconds();
	frame = ((int)(t * ENEMY_ANIM_FPS)) % data->enemy_frame_count;
	data->enemy_texture = data->enemy_frames[frame];
	return (&data->enemy_frames[frame]);
}

//calculates the corresponding texture coordinates for a specific 
//vertical segment of a sprite wave and retrieves its pixel color. 
//It then optionally applies an enemy hue gradient based on the animation 
//time before drawing the non-transparent pixel to the screen.
static void	draw_sprite_wave(t_cub3d *data, t_sprite_calc *sc,
	t_img *texture, t_sprite_wave *wave)
{
	int	tex_y;
	int	d;
	int	color;

	d = (wave->y - sc->v_offset) * 256 - data->current_height * 128
		+ sc->height * 128;
	tex_y = d * texture->height / sc->height / 256;
	if (tex_y >= 0 && tex_y < texture->height)
	{
		color = get_texture_pixel(texture, wave->tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
		{
			color = apply_enemy_hue_gradient(color, wave->stripe, wave->y,
					wave->anim_time);
			pixel_put(&data->img, wave->stripe, wave->y, color);
		}
	}
}

//draws a vertical column of the enemy on the screen 
//by iterating through its vertical bounds
static void	draw_sprite_column(t_cub3d *data, t_sprite_calc *sc,
	t_img *texture, int stripe)
{
	t_sprite_wave	wave;

	wave.tex_x = (int)((stripe - (-sc->width / 2 + sc->screen_x))
			* texture->width / sc->width);
	if (wave.tex_x < 0 || wave.tex_x >= texture->width)
		return ;
	wave.anim_time = get_time_in_seconds() * (ENEMY_HUE_SHIFT_SPEED * 0.06);
	wave.stripe = stripe;
	wave.y = sc->start_y;
	while (wave.y < sc->end_y)
	{
		draw_sprite_wave(data, sc, texture, &wave);
		wave.y++;
	}
}

//gets the current texture
//calculates the sprite's position and dimensions on the screen
//iterates through the vertical columns of the sprite and draws each column
static void	draw_single_enemy(t_cub3d *data, t_enemy *enemy)
{
	t_sprite_calc	sc;
	t_img			*texture;
	int				stripe;

	texture = get_current_enemy_texture(data);
	calc_sprite_transform(data, enemy, &sc);
	calc_sprite_dims(data, &sc);
	if (sc.height <= 0 || !texture || !texture->image)
		return ;
	stripe = sc.start_x;
	while (stripe < sc.end_x)
	{
		if (stripe >= 0 && stripe < data->current_width
			&& sc.ty < data->z_buffer[stripe])
			draw_sprite_column(data, &sc, texture, stripe);
		stripe++;
	}
}

void	render_enemies(t_cub3d *data)
{
	int		*order;
	double	*dist;
	int		i;

	if (data->map.enemy_count == 0 || !data->z_buffer
		|| !data->enemy_texture.image)
		return ;
	order = malloc(sizeof(int) * data->map.enemy_count);
	dist = malloc(sizeof(double) * data->map.enemy_count);
	if (!order || !dist)
	{
		free(order);
		free(dist);
		return ;
	}
	sort_enemies_by_dist(data, order, dist);
	i = -1;
	while (++i < data->map.enemy_count)
		draw_single_enemy(data, &data->map.enemies[order[i]]);
	free(order);
	free(dist);
}
