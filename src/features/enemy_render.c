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

static int	clamp_color(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

static int	is_whiteish_pixel(int r, int g, int b)
{
	int	min_c;
	int	max_c;

	min_c = r;
	if (g < min_c)
		min_c = g;
	if (b < min_c)
		min_c = b;
	max_c = r;
	if (g > max_c)
		max_c = g;
	if (b > max_c)
		max_c = b;
	if (min_c > 185 && (max_c - min_c) < 38)
		return (1);
	return (0);
}

static int	is_blueish_pixel(int r, int g, int b)
{
	if (b > 85 && b > r + 18 && b > g + 10)
		return (1);
	return (0);
}

static int	apply_enemy_hue_gradient(int color, int stripe, int y,
	double anim_time)
{
	int		r;
	int		g;
	int		b;
	int		target_r;
	int		target_g;
	int		target_b;
	double	phase;
	double	wave;
	double	wave_2;
	double	mix;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (is_whiteish_pixel(r, g, b))
		return (color);
	if (!is_blueish_pixel(r, g, b))
		return (color);
	phase = anim_time * 3.1 + stripe * 0.020 + y * 0.020;
	wave = (sin(phase) + 1.0) * 0.5;
	wave_2 = (sin(phase * 1.35 + 0.9) + 1.0) * 0.5;
	target_r = (int)(4.0 + 14.0 * wave_2);
	target_g = (int)(110.0 + 80.0 * wave);
	target_b = (int)(205.0 + 50.0 * wave_2);
	mix = 0.36 + 0.38 * wave;
	r = clamp_color((int)(r * (1.0 - mix) + target_r * mix));
	g = clamp_color((int)(g * (1.0 - mix) + target_g * mix));
	b = clamp_color((int)(b * (1.0 - mix) + target_b * mix));
	return ((r << 16) | (g << 8) | b);
}

static void	calc_sprite_transform(t_cub3d *data, t_enemy *enemy,
	t_sprite_calc *sc)
{
	sc->sx = enemy->pos_x / data->tile - data->player.pos_x / data->tile;
	sc->sy = enemy->pos_y / data->tile - data->player.pos_y / data->tile;
	sc->inv = 1.0 / (data->player.plane_x * data->player.dir_y
			- data->player.dir_x * data->player.plane_y);
	sc->tx = sc->inv * (data->player.dir_y * sc->sx
			- data->player.dir_x * sc->sy);
	sc->ty = sc->inv * (-data->player.plane_y * sc->sx
			+ data->player.plane_x * sc->sy);
}

static void	calc_sprite_dims(t_cub3d *data, t_sprite_calc *sc)
{
	double	plane_mag;
	double	fov_scale;

	if (sc->ty <= 0.01)
	{
		sc->height = 0;
		return ;
	}
	plane_mag = sqrt(data->player.plane_x * data->player.plane_x
			+ data->player.plane_y * data->player.plane_y);
	fov_scale = FOV_NORMAL / plane_mag;
	sc->screen_x = (int)((data->current_width / 2)
			* (1 + sc->tx / sc->ty));
	sc->height = (int)(data->current_height / sc->ty * fov_scale);
	sc->width = sc->height;
	sc->v_offset = (int)data->player.pitch + (int)data->player.z_offset;
	sc->start_y = -sc->height / 2 + data->current_height / 2 + sc->v_offset;
	if (sc->start_y < 0)
		sc->start_y = 0;
	sc->end_y = sc->height / 2 + data->current_height / 2 + sc->v_offset;
	if (sc->end_y >= data->current_height)
		sc->end_y = data->current_height - 1;
	sc->start_x = -sc->width / 2 + sc->screen_x;
	if (sc->start_x < 0)
		sc->start_x = 0;
	sc->end_x = sc->width / 2 + sc->screen_x;
	if (sc->end_x >= data->current_width)
		sc->end_x = data->current_width - 1;
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

static void	sort_enemies_by_dist(t_cub3d *data, int *order, double *dist)
{
	int		i;
	int		j;
	int		tmp_i;
	double	tmp_d;

	i = -1;
	while (++i < data->map.enemy_count)
	{
		order[i] = i;
		dist[i] = (data->player.pos_x / data->tile
				- data->map.enemies[i].pos_x / data->tile)
			* (data->player.pos_x / data->tile
				- data->map.enemies[i].pos_x / data->tile)
			+ (data->player.pos_y / data->tile
				- data->map.enemies[i].pos_y / data->tile)
			* (data->player.pos_y / data->tile
				- data->map.enemies[i].pos_y / data->tile);
	}
	i = -1;
	while (++i < data->map.enemy_count - 1)
	{
		j = i;
		while (++j < data->map.enemy_count)
		{
			if (dist[i] < dist[j])
			{
				tmp_d = dist[i];
				dist[i] = dist[j];
				dist[j] = tmp_d;
				tmp_i = order[i];
				order[i] = order[j];
				order[j] = tmp_i;
			}
		}
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
