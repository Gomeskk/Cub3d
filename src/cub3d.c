/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:12:33 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/09 03:09:04 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	data;

	init_data(&data);
	if (argc != 2)
		return (ft_putendl_fd(WRONG_ARGC, 2), 1);
	if (!check_map_name(argv[1]))
		return (ft_putendl_fd(WRONG_MAP_NAME, 2), 1);
	if (!read_map(argv[1], &data))
		return (free_all(&data), ft_putendl_fd(MAP_ERROR, 2), 1);
	if (!parse_identifiers(&data))
		return (free_all(&data), ft_putendl_fd(NO_IDENTIFIERS, 2), 1);
	if (!parse_map(&data))
		return (free_all(&data), ft_putendl_fd(WRONG_MAP, 2), 1);
	game_start(&data);
	free_all(&data);
}

/*
printf("Ceiling RGB = ");
print_rgb(data.textures.ceiling);

printf("Floor RGB = ");
print_rgb(data.textures.floor);
*/