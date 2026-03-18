
#include "cub3d.h"

/*
** Routes key press events to menu or gameplay handlers.
** keycode = X11 key code of the pressed key.
** Process: If status is not GAME (in menu), route to menu key handler,
** otherwise route to gameplay key handler.
*/
int	unified_key_press(int keycode, t_cub3d *data)
{
	if (data->status != GAME)
		return (key_press_handler(keycode, data));
	return (key_pressed(keycode, data));
}

/*
** Routes key release events to menu or gameplay handlers.
** keycode = X11 key code of the released key.
** Process: If status is not GAME (in menu), route to menu key release handler,
** otherwise route to gameplay key release handler.
*/
int	unified_key_release(int keycode, t_cub3d *data)
{
	if (data->status != GAME)
		return (key_release_handler(keycode, data));
	return (key_released(keycode, data));
}

/*
** Initializes game state on first frame after menu exits.
** game_initialized = static flag to run initialization only once.
** Process: Apply difficulty settings, cleanup menu resources, set mouse
** center position, lock and hide mouse cursor, render initial frame.
*/
static void	initialize_game_state(t_cub3d *data)
{
	apply_difficulty_settings(data);
	cleanup_menu(data);
	data->mouse.cx = data->current_width / 2;
	data->mouse.cy = data->current_height / 2;
	data->mouse.locked = 1;
	mlx_mouse_hide(data->mlx, data->window);
	data->mouse.x = data->mouse.cx;
	data->mouse.y = data->mouse.cy;
	raycast_render(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
}

/*
** Runs menu loop until GAME starts, then initializes first game frame.
** Uses static flag to ensure game initialization happens only once.
** Process: If in menu, run menu loop handler. If in GAME and not yet
** initialized, perform one-time game setup. Then run game render loop.
*/
int	unified_loop(t_cub3d *data)
{
	static int	game_initialized = 0;

	if (data->status != GAME)
		return (menu_loop_handler(data));
	if (!game_initialized)
	{
		game_initialized = 1;
		initialize_game_state(data);
	}
	return (render_game(data));
}
