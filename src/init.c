/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:32:48 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/06 22:21:35 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_data(t_cub3d *data)
{
    data->map.grid = NULL;
    data->map.map = NULL;
    data->map.start_point = 0;
    data->map.row_count = 0;
	data->map.col_count = 0;
    data->textures.no = NULL;
	data->textures.so = NULL;
	data->textures.ea = NULL;
	data->textures.we = NULL;
	data->textures.floor = -1;
	data->textures.ceiling = -1;
}
