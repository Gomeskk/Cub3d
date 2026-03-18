/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:17:59 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:18:02 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Load main menu and credits background images.
*/
int	init_start_game_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.screens.start_normal,
			"Png_images/StartGame/StartGame.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.start_hover,
			"Png_images/StartGame/Options.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.start_selected,
			"Png_images/StartGame/Credits.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.credits_screen,
			"Png_images/Credits/Credits.xpm") == -1)
		return (-1);
	return (0);
}

/*
** Load difficulty selection images (easy, medium, hard).
*/
int	init_difficulty_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.difficulty.easy,
			"Png_images/Difficulty/Easy.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.difficulty.medium,
			"Png_images/Difficulty/Medium.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.difficulty.hard,
			"Png_images/Difficulty/Hard.xpm") == -1)
		return (-1);
	return (0);
}

/*
** Load skin selection screen and left/right arrow images.
*/
int	init_skin_select_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.screens.skin_select,
			"Png_images/SkinSelection/SkinSelect.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_left,
			"Png_images/SkinSelection/ArrowLeft.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_right,
			"Png_images/SkinSelection/ArrowRight.xpm") == -1)
		return (-1);
	return (0);
}
