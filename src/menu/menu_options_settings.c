#include "../../inc/cub3d.h"

/*
** Adjust volume or sensibility setting
** Increments/decrements based on current section
** Clamps values to min/max bounds
*/
void	adjust_setting(t_cub3d *data, int direction)
{
	if (data->menu.options.section == SECTION_SOUND)
	{
		data->menu.options.volume_level += direction;
		if (data->menu.options.volume_level < VOLUME_MIN)
			data->menu.options.volume_level = VOLUME_MIN;
		if (data->menu.options.volume_level > VOLUME_MAX)
			data->menu.options.volume_level = VOLUME_MAX;
	}
	else if (data->menu.options.section == SECTION_SENSIBILITY)
	{
		data->menu.options.sensibility_level += direction;
		if (data->menu.options.sensibility_level < SENSIBILITY_MIN)
			data->menu.options.sensibility_level = SENSIBILITY_MIN;
		if (data->menu.options.sensibility_level > SENSIBILITY_MAX)
			data->menu.options.sensibility_level = SENSIBILITY_MAX;
	}
	render_options_menu(data);
}

/*
** Set arrow direction for resolution cycling
** THRESHOLD SYSTEM: Requires 2 presses to change direction, 1 to continue
** Prevents accidental changes when switching between up/down arrows
*/
int	set_arrow_direction(t_cub3d *data, int direction)
{
	int	threshold;

	if (data->menu.options.last_arrow_direction == direction)
		threshold = 1;
	else
	{
		data->menu.options.resolution_arrow_count = 0;
		threshold = 2;
	}
	data->menu.options.last_arrow_direction = direction;
	data->menu.options.resolution_arrow_count++;
	return (threshold);
}

/*
** Apply resolution level change if threshold met
** Increments/decrements pending resolution level within valid range
** Arrow count resets after each successful change
*/
void	apply_resolution_change(t_cub3d *data, int dir, int threshold)
{
	if (data->menu.options.resolution_arrow_count >= threshold)
	{
		if (dir == 1 && data->menu.options.pending_resolution_level < RESOLUTION_MAX)
			data->menu.options.pending_resolution_level++;
		else if (dir == -1 && data->menu.options.pending_resolution_level > RESOLUTION_MIN)
			data->menu.options.pending_resolution_level--;
		data->menu.options.resolution_arrow_count = 0;
	}
	render_options_menu(data);
}

