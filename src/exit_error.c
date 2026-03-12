/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:14:59 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/12 22:44:54 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_wall_textures(t_cub3d *data)
{
	void	*images[11];
	int		i;
	int		j;
	int		already_destroyed;

	images[0] = data->wall_textures.north.image;
	images[1] = data->wall_textures.south.image;
	images[2] = data->wall_textures.east.image;
	images[3] = data->wall_textures.west.image;
	images[4] = data->wall_textures.door.image;
	images[5] = data->wall_textures.button.image;
	images[6] = data->wall_textures.alt_button.image;
	images[7] = data->wall_textures.alt_north.image;
	images[8] = data->wall_textures.alt_south.image;
	images[9] = data->wall_textures.alt_east.image;
	images[10] = data->wall_textures.alt_west.image;
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

void	free_all(t_cub3d *data)
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
	if (data->mlx)
		destroy_wall_textures(data);
	if (data->enemy_texture.image)
		mlx_destroy_image(data->mlx, data->enemy_texture.image);
	if (data->img.image)
		mlx_destroy_image(data->mlx, data->img.image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	exit_error(t_cub3d *data, char *message)
{
	ft_putendl_fd(message, 2);
	free_all(data);
	exit(127);
}

void	exit_game(char *end_game, t_cub3d *data)
{
	free_all(data);
	ft_putendl_fd(end_game, 1);
	exit(0);
}

int	x_window(t_cub3d *data)
{
	exit_game("Thank you for Playing \033[1;35mbpires-r's\033[1;0m and \033[1;35mjoafaust's\033[1;0m game!", data);
	return (0);
}
