#include "../../inc/cub3d.h"
#include <sys/time.h>

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	set_key_state(int keycode, t_cub3d *data, int state)
{
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = state;
	else if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = state;
	else if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = state;
	else if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = state;
}

int	key_press_handler(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape && data->status == MAIN_MENU_SCREEN)
		exit(0);
	set_key_state(keycode, data, 1);
	if (keycode == XK_Return || keycode == XK_Tab || keycode == XK_Escape)
		return (menu_key_handler(keycode, data));
	return (0);
}

int	key_release_handler(int keycode, t_cub3d *data)
{
	set_key_state(keycode, data, 0);
	return (0);
}

static void	handle_throttled_vertical_key(t_cub3d *data, int key,
				long current_time, long *last_time)
{
	if (current_time - *last_time < KEY_THROTTLE_MS)
		return ;
	*last_time = current_time;
	if (data->status == MAIN_MENU_SCREEN)
		handle_main_menu_keys(key, data);
	else if (data->status == DIFFICULTY_SCREEN)
		handle_difficulty_keys(key, data);
	else if (data->status == OPTIONS_SCREEN)
		handle_options_screen_keys(key, data);
}

static void	handle_throttled_horizontal_key(t_cub3d *data, int key,
				long current_time, long *last_time)
{
	if (data->status != OPTIONS_SCREEN)
		return ;
	if (current_time - *last_time < KEY_THROTTLE_MS)
		return ;
	*last_time = current_time;
	handle_options_screen_keys(key, data);
}

int	menu_loop_handler(t_cub3d *data)
{
	static long	last_w = 0;
	static long	last_s = 0;
	static long	last_a = 0;
	static long	last_d = 0;
	long		current_time;

	current_time = get_time_ms();
	if (data->keys.w)
		handle_throttled_vertical_key(data, XK_w, current_time, &last_w);
	if (data->keys.s)
		handle_throttled_vertical_key(data, XK_s, current_time, &last_s);
	if (data->keys.a)
		handle_throttled_horizontal_key(data, XK_a, current_time, &last_a);
	if (data->keys.d)
		handle_throttled_horizontal_key(data, XK_d, current_time, &last_d);
	return (0);
}

