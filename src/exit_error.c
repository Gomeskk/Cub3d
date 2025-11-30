/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:14:59 by bpires-r          #+#    #+#             */
/*   Updated: 2025/11/30 20:13:41 by bpires-r         ###   ########.fr       */
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
}