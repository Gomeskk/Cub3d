/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:12:33 by bpires-r          #+#    #+#             */
/*   Updated: 2025/10/26 18:17:32 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_cub3d	data;
	
	if (argc != 2)
		return (ft_putendl_fd(WRONG_ARGC, 2), 1);
	if (!check_map_name(argv[1]))
		return (ft_putendl_fd(WRONG_MAP, 2), 1);
	if (!read_map(argv[1], &data))
		return (ft_putendl_fd(MAP_ERROR, 2), 1);
	free_ar((void **)data.map.map);
}

