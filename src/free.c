/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:20:41 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 23:21:20 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Destroys wall textures once each, skipping duplicated pointers.
*/
static void	destroy_wall_textures(t_cub3d *data)
{
	void	*images[11];
	int		i;
	int		j;
	int		already_destroyed;

	fill_wall_images(data, images);
	i = 0;
	while (i < 11)
	{
		already_destroyed = 0;
		j = 0;
		while (j < i)
		{
			if (images[i] && images[i] == images[j])
			{
				already_destroyed = 1;
				break ;
			}
			j++;
		}
		if (images[i] && !already_destroyed)
			mlx_destroy_image(data->mlx, images[i]);
		i++;
	}
}

static void	free_non_graphic_data(t_cub3d *data)
{
	if (data->textures.ea)
		free(data->textures.ea);
	if (data->textures.no)
		free(data->textures.no);
	if (data->textures.we)
		free(data->textures.we);
	if (data->textures.so)
		free(data->textures.so);
	if (data->map.map)
		free_ar((void **)data->map.map);
	if (data->map.grid)
		free_ar((void **)data->map.grid);
	if (data->map.doors)
		free(data->map.doors);
	if (data->map.buttons)
		free(data->map.buttons);
	if (data->map.enemies)
		free(data->map.enemies);
	if (data->z_buffer)
		free(data->z_buffer);
}

static void	destroy_enemy_textures(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < ENEMY_ANIM_FRAMES)
	{
		if (data->enemy_frames[i].image)
			mlx_destroy_image(data->mlx, data->enemy_frames[i].image);
		i++;
	}
}

static void	destroy_hands_textures(t_cub3d *data)
{
	int	skin;

	skin = 0;
	while (skin < HAND_SKIN_COUNT)
	{
		if (data->hands.skins[skin].image)
			mlx_destroy_image(data->mlx, data->hands.skins[skin].image);
		skin++;
	}
}

/*
** Releases all allocated resources and tears down mlx objects.
*/
void	free_all(t_cub3d *data)
{
	free_non_graphic_data(data);
	if (data->mlx)
	{
		destroy_wall_textures(data);
		destroy_enemy_textures(data);
		destroy_hands_textures(data);
		if (data->img.image)
			mlx_destroy_image(data->mlx, data->img.image);
		if (data->window)
			mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
