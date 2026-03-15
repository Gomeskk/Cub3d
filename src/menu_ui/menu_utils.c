#include "../../inc/cub3d.h"
#include <sys/time.h>

// Convert menu sensibility level (0-4) to multiplier
double	get_sensibility_multiplier(int level)
{
	static const double multipliers[] = {0.0, 0.5, 1.0, 1.5, 2.0};
	
	if (level < 0 || level > 4)
		return (1.0);
	return (multipliers[level]);
}

void	apply_difficulty_settings(t_cub3d *data)
{
	int	i;

	if (data->menu.difficulty_choice == DIFF_EASY)
		data->game_settings.difficulty_mult = 0.60;
	else if (data->menu.difficulty_choice == DIFF_MEDIUM)
		data->game_settings.difficulty_mult = 1.0;
	else if (data->menu.difficulty_choice == DIFF_HARD)
		data->game_settings.difficulty_mult = 1.25;
	
	// Update all existing enemies with new difficulty values
	i = 0;
	while (i < data->map.enemy_count)
	{
		data->map.enemies[i].speed = ENEMY_SPEED_BASE * data->game_settings.difficulty_mult;
		data->map.enemies[i].vision_radius = ENEMY_VISION_RADIUS * data->game_settings.difficulty_mult;
		i++;
	}
}

void	init_fps_counter(t_fps_counter *fps)
{
	fps->last_time = get_time_in_seconds();
	fps->frame_count = 0;
	fps->fps = 0;
}

void	update_fps_counter(t_fps_counter *fps)
{
	double	current_time;
	double	elapsed;

	fps->frame_count++;
	current_time = get_time_in_seconds();
	elapsed = current_time - fps->last_time;
	if (elapsed >= 1.0)
	{
		fps->fps = (int)(fps->frame_count / elapsed);
		fps->frame_count = 0;
		fps->last_time = current_time;
	}
}

void	render_fps(t_cub3d *data)
{
	char	*fps_num;
	char	*fps_text;
	int		text_x;
	int		text_y;

	fps_num = ft_itoa(data->fps.fps);
	if (!fps_num)
		return ;
	fps_text = ft_strjoin("FPS: ", fps_num);
	free(fps_num);
	if (!fps_text)
		return ;
	text_x = data->current_width - 100;
	text_y = 20;
	mlx_string_put(data->mlx, data->window, text_x, text_y, 0x00FF00, fps_text);
	free(fps_text);
}
