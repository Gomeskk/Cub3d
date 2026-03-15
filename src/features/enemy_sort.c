#include "cub3d.h"

void	calc_sprite_transform(t_cub3d *data, t_enemy *enemy,
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

void	calc_sprite_dims(t_cub3d *data, t_sprite_calc *sc)
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

void	sort_enemies_by_dist(t_cub3d *data, int *order, double *dist)
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