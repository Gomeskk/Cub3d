#include "cub3d.h"

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

static void	draw_sprite_column(t_cub3d *data, t_sprite_calc *sc, int stripe)
{
	int	tex_x;
	int	tex_y;
	int	y;
	int	d;
	int	color;

	tex_x = (int)((stripe - (-sc->width / 2 + sc->screen_x))
			* data->enemy_texture.width / sc->width);
	if (tex_x < 0 || tex_x >= data->enemy_texture.width)
		return ;
	y = sc->start_y;
	while (y < sc->end_y)
	{
		d = (y - sc->v_offset) * 256 - data->current_height * 128
			+ sc->height * 128;
		tex_y = d * data->enemy_texture.height / sc->height / 256;
		if (tex_y >= 0 && tex_y < data->enemy_texture.height)
		{
			color = get_texture_pixel(&data->enemy_texture, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				pixel_put(&data->img, stripe, y, color);
		}
		y++;
	}
}

static void	draw_single_enemy(t_cub3d *data, t_enemy *enemy)
{
	t_sprite_calc	sc;
	int				stripe;

	calc_sprite_transform(data, enemy, &sc);
	calc_sprite_dims(data, &sc);
	if (sc.height <= 0)
		return ;
	stripe = sc.start_x;
	while (stripe < sc.end_x)
	{
		if (stripe >= 0 && stripe < data->current_width
			&& sc.ty < data->z_buffer[stripe])
			draw_sprite_column(data, &sc, stripe);
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
