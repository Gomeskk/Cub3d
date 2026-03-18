
#include "cub3d.h"

/*
** Updates player and world state, then renders a complete gameplay frame.
** delta_time = time elapsed since last frame in seconds.
** Process: Update player movement and jump, update enemies AI and detection,
** check enemy collision (game over if caught), update camera rotation from
** mouse and keyboard, render 3D view, optionally render minimap overlay,
** display frame to window, update and render FPS counter, sync display.
*/
void	render_game_frame(t_cub3d *data, double delta_time)
{
	data->frame_dt = delta_time;
	player_movement(data, delta_time);
	player_jump(data, delta_time);
	update_enemies(data, delta_time);
	check_enemy_detection(data);
	if (check_enemy_collision(data))
		exit_game("An enemy caught you! Game Over!", data);
	update_mouse_rotation(data, delta_time);
	update_keyboard_rotation(data, delta_time);
	raycast_render(data);
	if (data->player.minimap_visible)
		render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	update_fps_counter(&data->fps);
	render_fps(data);
	mlx_do_sync(data->mlx);
}

/*
** Runs the gameplay loop at the configured FPS cadence.
** Uses static variable to accumulate time between frames.
** Process: Accumulate delta time from system clock. When enough time has
** passed for one frame (1/FPS seconds), handle all toggles, render the frame,
** and reset time counter. Returns 0 to continue MLX loop.
*/
int	render_game(t_cub3d *data)
{
	static double	accumulated_time;

	accumulated_time += get_delta_time();
	if (accumulated_time >= 1.0 / FPS)
	{
		handle_game_toggles(data);
		render_game_frame(data, accumulated_time);
		accumulated_time = 0;
	}
	return (0);
}
