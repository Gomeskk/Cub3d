#include "../../inc/cub3d.h"
#include <sys/time.h>

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	handle_throttled_key(t_cub3d *data, int is_pressed,
			long *last_time, int keycode)
{
	long	current_time;

	if (!is_pressed)
		return ;
	current_time = get_time_ms();
	if (current_time - *last_time < KEY_THROTTLE_MS)
		return ;
	*last_time = current_time;
	if (data->status == MAIN_MENU_SCREEN)
		handle_main_menu_keys(keycode, data);
	else if (data->status == DIFFICULTY_SCREEN)
		handle_difficulty_keys(keycode, data);
	else if (data->status == CREDITS)
		handle_credits_keys(keycode, data);
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

int	menu_loop_handler(t_cub3d *data)
{
	static long	last_w = 0;
	static long	last_s = 0;
	static long	last_a = 0;
	static long	last_d = 0;

	handle_throttled_key(data, data->keys.w, &last_w, XK_w);
	handle_throttled_key(data, data->keys.s, &last_s, XK_s);
	if (data->status == CREDITS)
	{
		handle_throttled_key(data, data->keys.a, &last_a, XK_a);
		handle_throttled_key(data, data->keys.d, &last_d, XK_d);
	}
	return (0);
}
