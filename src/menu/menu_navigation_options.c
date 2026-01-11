#include "../../inc/cub3d.h"

void	adjust_setting(t_cub3d *data, int direction)
{
	if (data->menu.options_section == 0)
	{
		data->menu.volume_level += direction;
		if (data->menu.volume_level < 0)
			data->menu.volume_level = 0;
		if (data->menu.volume_level > 14)
			data->menu.volume_level = 14;
	}
	else if (data->menu.options_section == 2)
	{
		data->menu.sensibility_level += direction;
		if (data->menu.sensibility_level < 0)
			data->menu.sensibility_level = 0;
		if (data->menu.sensibility_level > 4)
			data->menu.sensibility_level = 4;
	}
	render_credits(data);
}

void	handle_horizontal_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Left || keycode == XK_a)
		adjust_setting(data, -1);
	else if (keycode == XK_Right || keycode == XK_d)
		adjust_setting(data, 1);
}

int	set_arrow_direction(t_cub3d *data, int direction)
{
	int	threshold;

	if (data->menu.last_arrow_direction == direction)
		threshold = 1;
	else
	{
		data->menu.resolution_arrow_count = 0;
		threshold = 2;
	}
	data->menu.last_arrow_direction = direction;
	data->menu.resolution_arrow_count++;
	return (threshold);
}

void	apply_resolution_change(t_cub3d *data, int dir, int threshold)
{
	if (data->menu.resolution_arrow_count >= threshold)
	{
		if (dir == 1 && data->menu.resolution_level < 4)
			data->menu.resolution_level++;
		else if (dir == -1 && data->menu.resolution_level > 0)
			data->menu.resolution_level--;
		data->menu.resolution_arrow_count = 0;
	}
	render_credits(data);
}

void	handle_vertical_keys(int keycode, t_cub3d *data)
{
	int	threshold;
	int	direction;

	if (data->menu.options_section != 1)
		return ;
	if (keycode == XK_Up || keycode == XK_w)
		direction = 1;
	else if (keycode == XK_Down || keycode == XK_s)
		direction = -1;
	else
		return ;
	threshold = set_arrow_direction(data, direction);
	apply_resolution_change(data, direction, threshold);
}
