#include "../../inc/cub3d.h"

void	adjust_setting(t_cub3d *data, int direction)
{
	if (data->menu.options_section == SECTION_SOUND)
	{
		data->menu.volume_level += direction;
		if (data->menu.volume_level < VOLUME_MIN)
			data->menu.volume_level = VOLUME_MIN;
		if (data->menu.volume_level > VOLUME_MAX)
			data->menu.volume_level = VOLUME_MAX;
	}
	else if (data->menu.options_section == SECTION_SENSIBILITY)
	{
		data->menu.sensibility_level += direction;
		if (data->menu.sensibility_level < SENSIBILITY_MIN)
			data->menu.sensibility_level = SENSIBILITY_MIN;
		if (data->menu.sensibility_level > SENSIBILITY_MAX)
			data->menu.sensibility_level = SENSIBILITY_MAX;
	}
	render_credits(data);
}

void	handle_horizontal_keys(int keycode, t_cub3d *data)
{
	if (data->menu.resolution_confirm_active)
	{
		if (keycode == XK_Left || keycode == XK_a)
			data->menu.resolution_confirm_choice = 1;
		else if (keycode == XK_Right || keycode == XK_d)
			data->menu.resolution_confirm_choice = 0;
		render_credits(data);
	}
	else
	{
		if (keycode == XK_Left || keycode == XK_a)
			adjust_setting(data, -1);
		else if (keycode == XK_Right || keycode == XK_d)
			adjust_setting(data, 1);
	}
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
		if (dir == 1 && data->menu.pending_resolution_level < RESOLUTION_MAX)
			data->menu.pending_resolution_level++;
		else if (dir == -1 && data->menu.pending_resolution_level > RESOLUTION_MIN)
			data->menu.pending_resolution_level--;
		data->menu.resolution_arrow_count = 0;
	}
	render_credits(data);
}

void	handle_vertical_keys(int keycode, t_cub3d *data)
{
	int	threshold;
	int	direction;

	if (data->menu.options_section != SECTION_RESOLUTION)
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

void	handle_enter_key(t_cub3d *data)
{
	if (data->menu.resolution_confirm_active)
	{
		if (data->menu.resolution_confirm_choice == 1)
		{
			apply_resolution(data, data->menu.pending_resolution_level);
		}
		data->menu.resolution_confirm_active = 0;
		render_credits(data);
	}
	else if (data->menu.options_section == SECTION_RESOLUTION
		&& data->menu.pending_resolution_level != data->menu.resolution_level)
	{
		data->menu.resolution_confirm_active = 1;
		data->menu.resolution_confirm_choice = 0;
		render_credits(data);
	}
}
