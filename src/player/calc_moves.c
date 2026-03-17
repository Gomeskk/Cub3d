#include "cub3d.h"

static void	calc_move_ws(t_cub3d *data, double *dx, double *dy)
{
	if (data->keys.w)
	{
		*dx += data->player.dir_x;
		*dy += data->player.dir_y;
	}
	if (data->keys.s)
	{
		*dx -= data->player.dir_x;
		*dy -= data->player.dir_y;
	}
}

static void	calc_move_ad(t_cub3d *data, double *dx, double *dy)
{
	if (data->keys.a)
	{
		*dx += data->player.dir_y;
		*dy += -data->player.dir_x;
	}
	if (data->keys.d)
	{
		*dx -= data->player.dir_y;
		*dy -= -data->player.dir_x;
	}
}

void	calc_movement_direction(t_cub3d *data, double *dx, double *dy)
{
	*dx = 0.0;
	*dy = 0.0;
	if (data->keys.w || data->keys.s)
		calc_move_ws(data, dx, dy);
	if (data->keys.a || data->keys.d)
		calc_move_ad(data, dx, dy);
	if (*dx != 0.0 && *dy != 0.0)
	{
		*dx *= DIAGONAL_FACTOR;
		*dy *= DIAGONAL_FACTOR;
	}
}
