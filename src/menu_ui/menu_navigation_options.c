#include "../../inc/cub3d.h"

void	handle_horizontal_keys(int keycode, t_cub3d *data)
{
	if (data->menu.options.resolution_confirm_active)
	{
		if (keycode == XK_Left || keycode == XK_a)
			data->menu.options.resolution_confirm_choice = 1;
		else if (keycode == XK_Right || keycode == XK_d)
			data->menu.options.resolution_confirm_choice = 0;
		render_options_menu(data);
	}
	else
	{
		if (keycode == XK_Left || keycode == XK_a)
			adjust_setting(data, -1);
		else if (keycode == XK_Right || keycode == XK_d)
			adjust_setting(data, 1);
	}
}

void	handle_vertical_keys(int keycode, t_cub3d *data)
{
	int	threshold;
	int	direction;

	if (data->menu.options.section != SECTION_RESOLUTION)
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
	if (data->menu.options.resolution_confirm_active)
	{
		if (data->menu.options.resolution_confirm_choice == 1)
		{
			apply_resolution(data, data->menu.options.pending_resolution_level);
		}
		data->menu.options.resolution_confirm_active = 0;
		render_options_menu(data);
	}
	else if (data->menu.options.section == SECTION_RESOLUTION
		&& data->menu.options.pending_resolution_level != data->menu.options.resolution_level)
	{
		data->menu.options.resolution_confirm_active = 1;
		data->menu.options.resolution_confirm_choice = 0;
		render_options_menu(data);
	}
}

static int	handle_escape_in_options(t_cub3d *data)
{
	if (data->menu.options.resolution_confirm_active)
	{
		data->menu.options.resolution_confirm_active = 0;
		render_options_menu(data);
		return (0);
	}
	data->menu.menu_choice = MENU_START;
	data->status = MAIN_MENU_SCREEN;
	data->menu.options.section = SECTION_SOUND;
	render_main_menu(data);
	return (0);
}

int	handle_options_screen_keys(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
		return (handle_escape_in_options(data));
	else if (keycode == XK_Return)
		handle_enter_key(data);
	else if (keycode == XK_Tab)
	{
		data->menu.options.section = (data->menu.options.section + 1) % SECTION_COUNT;
		render_options_menu(data);
	}
	else if (keycode == XK_Left || keycode == XK_a
		|| keycode == XK_Right || keycode == XK_d)
		handle_horizontal_keys(keycode, data);
	else if (keycode == XK_Up || keycode == XK_w
		|| keycode == XK_Down || keycode == XK_s)
		handle_vertical_keys(keycode, data);
	return (0);
}
