/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:14:59 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/10 17:47:19 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (data->img.image)
		mlx_destroy_image(data->mlx, data->img.image);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
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
