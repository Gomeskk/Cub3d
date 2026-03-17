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

static void	set_sprite_vertical_bounds(t_cub3d *data, t_sprite_calc *sc)
{
	sc->v_offset = (int)data->player.pitch + (int)data->player.z_offset;
	sc->start_y = -sc->height / 2 + data->current_height / 2 + sc->v_offset;
	if (sc->start_y < 0)
		sc->start_y = 0;
	sc->end_y = sc->height / 2 + data->current_height / 2 + sc->v_offset;
	if (sc->end_y >= data->current_height)
		sc->end_y = data->current_height - 1;
}

static void	set_sprite_horizontal_bounds(t_cub3d *data, t_sprite_calc *sc)
{
	sc->start_x = -sc->width / 2 + sc->screen_x;
	if (sc->start_x < 0)
		sc->start_x = 0;
	sc->end_x = sc->width / 2 + sc->screen_x;
	if (sc->end_x >= data->current_width)
		sc->end_x = data->current_width - 1;
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
	set_sprite_vertical_bounds(data, sc);
	set_sprite_horizontal_bounds(data, sc);
}
