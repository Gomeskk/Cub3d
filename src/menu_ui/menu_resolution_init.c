/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_resolution_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:18:38 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/18 22:18:39 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Create new window with specified dimensions
** Returns 1 on success, 0 on failure
** Also updates current_width and current_height tracking variables
*/
int	create_new_window(t_cub3d *data, int width, int height)
{
	data->window = mlx_new_window(data->mlx, width, height, "Cub3D");
	if (!data->window)
		return (0);
	mlx_do_sync(data->mlx);
	data->current_width = width;
	data->current_height = height;
	return (1);
}

/*
** Create menu screen buffer for new resolution
** DOUBLE BUFFERING: All menu elements are drawn to this buffer first,
** then the complete buffer is displayed to window (prevents flickering)
** Returns 1 on success, 0 on failure
*/
int	create_menu_buffer(t_cub3d *data, int width, int height)
{
	data->menu.screens.screen_buffer.image = mlx_new_image(data->mlx,
			width, height);
	if (!data->menu.screens.screen_buffer.image)
		return (0);
	data->menu.screens.screen_buffer.data = mlx_get_data_addr(
			data->menu.screens.screen_buffer.image,
			&data->menu.screens.screen_buffer.bpp,
			&data->menu.screens.screen_buffer.size_line,
			&data->menu.screens.screen_buffer.endian);
	data->menu.screens.screen_buffer.width = width;
	data->menu.screens.screen_buffer.height = height;
	return (1);
}

/*
** Create game rendering image for new resolution
** This is where the 3D raycasting output is drawn
** Returns 1 on success, 0 on failure
*/
int	create_game_image(t_cub3d *data, int width, int height)
{
	data->img.image = mlx_new_image(data->mlx, width, height);
	if (!data->img.image)
		return (0);
	data->img.data = mlx_get_data_addr(data->img.image,
			&data->img.bpp, &data->img.size_line, &data->img.type);
	data->img.width = width;
	data->img.height = height;
	free(data->z_buffer);
	data->z_buffer = malloc(sizeof(double) * width);
	return (1);
}

// Update resolution tracking and mouse center position
void	update_resol_settings(t_cub3d *data, int level, int width, int height)
{
	data->menu.options.resolution_level = level;
	data->mouse.cx = width / 2;
	data->mouse.cy = height / 2;
}
