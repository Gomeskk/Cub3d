#include "cub3d.h"

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

static void	draw_sprite_column(t_cub3d *data, t_sprite_calc *sc,
	t_img *texture, int stripe)
{
	int	tex_x;
	int	tex_y;
	int	y;
	int	d;
	int	color;
	double	anim_time;

	tex_x = (int)((stripe - (-sc->width / 2 + sc->screen_x))
			* texture->width / sc->width);
	if (tex_x < 0 || tex_x >= texture->width)
		return ;
	anim_time = get_time_in_seconds() * (ENEMY_HUE_SHIFT_SPEED * 0.06);
	y = sc->start_y;
	while (y < sc->end_y)
	{
		d = (y - sc->v_offset) * 256 - data->current_height * 128
			+ sc->height * 128;
		tex_y = d * texture->height / sc->height / 256;
		if (tex_y >= 0 && tex_y < texture->height)
		{
			color = get_texture_pixel(texture, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
			{
				color = apply_enemy_hue_gradient(color, stripe, y, anim_time);
				pixel_put(&data->img, stripe, y, color);
			}
		}
		y++;
	}
}

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
