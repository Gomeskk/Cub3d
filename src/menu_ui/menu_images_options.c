/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_images_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:17:49 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:17:52 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Load base options screen assets and tab highlight images.
*/
static int	init_options_base_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx, &data->menu.screens.options_screen,
			"Png_images/Options/OptionsMenu.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_up,
			"Png_images/Arrow/UP(PINK).xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.screens.arrow_down,
			"Png_images/Arrow/DOWN(PINK).xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.tab_sound,
			"Png_images/TabChoices/TabSound.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.tab_resol,
			"Png_images/TabChoices/TabResolution.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx, &data->menu.options_imgs.tab_sensibility,
			"Png_images/TabChoices/TabSensibility.xpm") == -1)
		return (-1);
	return (0);
}

/*
** Load resolution confirmation assets and option image arrays.
*/
static int	init_options_resolution_images(t_cub3d *data)
{
	if (load_xpm_with_data(data->mlx,
			&data->menu.options_imgs.resolution_approve,
			"Png_images/ScreenSize/ResolutionAprove.xpm") == -1)
		return (-1);
	if (load_xpm_with_data(data->mlx,
			&data->menu.options_imgs.resolution_decline,
			"Png_images/ScreenSize/ResolutionDeclined.xpm") == -1)
		return (-1);
	if (init_volume_images(data) == -1)
		return (-1);
	if (init_sensibility_images(data) == -1)
		return (-1);
	if (init_resolution_images(data) == -1)
		return (-1);
	return (0);
}

/*
** Initialize all options menu images.
*/
int	init_options_images(t_cub3d *data)
{
	if (init_options_base_images(data) == -1)
		return (-1);
	if (init_options_resolution_images(data) == -1)
		return (-1);
	return (0);
}
