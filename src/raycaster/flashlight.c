
#include "cub3d.h"

# define FLASHLIGHT_RADIUS 0.45
# define FLASHLIGHT_MIN_LIGHT 0.14

static int	get_pixel(t_img *img, int x, int y)
{
	return (*(int *)(img->data + y * img->size_line
			+ x * (img->bpp / 8)));
}

static int	darken_pixel(int color, double brightness)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * brightness);
	g = (int)(((color >> 8) & 0xFF) * brightness);
	b = (int)((color & 0xFF) * brightness);
	return ((r << 16) | (g << 8) | b);
}

static double	get_brightness(t_cub3d *data, int x, int y)
{
	double	cx;
	double	cy;
	double	radius2;
	double	dx;
	double	dy;
	double	dist2;
	double	min_light;

	cx = data->current_width / 2.0;
	cy = data->current_height / 2.0;
	radius2 = data->current_height * FLASHLIGHT_RADIUS;
	radius2 = radius2 * radius2;
	min_light = FLASHLIGHT_MIN_LIGHT;
	dx = x - cx;
	dy = y - cy;
	dist2 = (dx * dx + dy * dy) / radius2;
	if (dist2 >= 1.0)
		return (min_light);
	return (1.0 - (1.0 - min_light) * dist2 * dist2);
}

void	apply_flashlight(t_cub3d *data)
{
	int	x;
	int	y;

	if (!data->player.flashlight_on)
		return ;
	y = 0;
	while (y < data->current_height)
	{
		x = 0;
		while (x < data->current_width)
		{
			pixel_put(&data->img, x, y,
				darken_pixel(get_pixel(&data->img, x, y),
					get_brightness(data, x, y)));
			x++;
		}
		y++;
	}
}
