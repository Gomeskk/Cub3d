/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:18:54 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/19 21:13:27 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Convert menu sensibility level (0-4) to movement multiplier.
*/
double	get_sensibility_multiplier(int level)
{
	if (level < 0 || level > 4)
		return (1.0);
	if (level == 0)
		return (0.0);
	else if (level == 1)
		return (0.5);
	else if (level == 2)
		return (1.0);
	else if (level == 3)
		return (1.5);
	return (2.0);
}

/*
** Apply current difficulty multiplier to all active enemies.
*/
void	apply_difficulty_settings(t_cub3d *data)
{
	int	i;

	if (data->menu.difficulty_choice == DIFF_EASY)
		data->game_settings.difficulty_mult = 0.60;
	else if (data->menu.difficulty_choice == DIFF_MEDIUM)
		data->game_settings.difficulty_mult = 1.0;
	else if (data->menu.difficulty_choice == DIFF_HARD)
		data->game_settings.difficulty_mult = 1.25;
	i = 0;
	while (i < data->map.enemy_count)
	{
		data->map.enemies[i].speed = ENEMY_SPEED_BASE * data->tile
			* data->game_settings.difficulty_mult;
		data->map.enemies[i].vision_radius = ENEMY_VISION_RADIUS
			* data->game_settings.difficulty_mult;
		i++;
	}
}

/*
** Initialize FPS counter state.
*/
void	init_fps_counter(t_fps_counter *fps)
{
	fps->last_time = get_time_in_seconds();
	fps->frame_count = 0;
	fps->fps = 0;
}

/*
** Update FPS counter once per rendered frame.
*/
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

/*
** Draw FPS text overlay in the top-right corner.
*/
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
