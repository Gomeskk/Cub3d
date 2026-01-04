#include "../../inc/cub3d.h"
#include <sys/time.h>

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	key_press_handler(int keycode, t_cub3d *data)
{
	if (keycode == KEY_ESC)
	{
		if (data->status == MAIN_MENU_SCREEN)
			exit(0);
	}
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = 1;
	if (keycode == XK_Return || keycode == XK_space)
		return (menu_key_handler(keycode, data));
	if (keycode == XK_Tab || keycode == KEY_TAB)
		return (menu_key_handler(keycode, data));
	if (keycode == KEY_ESC)
		return (menu_key_handler(keycode, data));
	return (0);
}

int	key_release_handler(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = 0;
	return (0);
}

int	menu_loop_handler(t_cub3d *data)
{
	static long	last_time = 0;
	long		current_time;

	current_time = get_time_ms();
	if (current_time - last_time < 150)
		return (0);
	if (data->keys.w)
	{
		last_time = current_time;
		if (data->status == MAIN_MENU_SCREEN)
			handle_main_menu_keys(XK_w, data);
		else if (data->status == DIFFICULTY_SCREEN)
			handle_difficulty_keys(XK_w, data);
		else if (data->status == CREDITS)
			handle_credits_keys(XK_w, data);
	}
	else if (data->keys.s)
	{
		last_time = current_time;
		if (data->status == MAIN_MENU_SCREEN)
			handle_main_menu_keys(XK_s, data);
		else if (data->status == DIFFICULTY_SCREEN)
			handle_difficulty_keys(XK_s, data);
		else if (data->status == CREDITS)
			handle_credits_keys(XK_s, data);
	}
	else if (data->keys.a && data->status == CREDITS)
	{
		last_time = current_time;
		handle_credits_keys(XK_a, data);
	}
	else if (data->keys.d && data->status == CREDITS)
	{
		last_time = current_time;
		handle_credits_keys(XK_d, data);
	}
	return (0);
}
