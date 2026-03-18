/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:18:42 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:18:43 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Get resolution dimensions from level index
** LOOKUP TABLE: Uses const arrays to map level (0-4) to actual dimensions
** This is faster than switch/if-else and keeps resolution data centralized
** Levels: 0=960x540, 1=1280x720, 2=1600x900, 3=1920x1080, 4=custom
*/
static void	get_resolution_dimensions(int level, int *width, int *height)
{
	const int	widths[5] = {RES_0_WIDTH, RES_1_WIDTH, RES_2_WIDTH,
		RES_3_WIDTH, RES_4_WIDTH};
	const int	heights[5] = {RES_0_HEIGHT, RES_1_HEIGHT, RES_2_HEIGHT,
		RES_3_HEIGHT, RES_4_HEIGHT};

	*width = widths[level];
	*height = heights[level];
}

// Destroy old window and images to free memory before creating new ones
static void	destroy_old_resources(t_cub3d *data)
{
	if (data->menu.screens.screen_buffer.image)
		mlx_destroy_image(data->mlx, data->menu.screens.screen_buffer.image);
	if (data->img.image)
		mlx_destroy_image(data->mlx, data->img.image);
	mlx_destroy_window(data->mlx, data->window);
}

// Aply new resolution - complete window/image recreation
void	apply_resolution(t_cub3d *data, int new_level)
{
	int	new_width;
	int	new_height;

	get_resolution_dimensions(new_level, &new_width, &new_height);
	destroy_old_resources(data);
	if (!create_new_window(data, new_width, new_height))
		return ;
	if (!create_menu_buffer(data, new_width, new_height))
		return ;
	if (!create_game_image(data, new_width, new_height))
		return ;
	update_resol_settings(data, new_level, new_width, new_height);
	reattach_hooks(data);
}
