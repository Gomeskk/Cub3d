/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:37:17 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/01 16:57:24 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_rgb(int color)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	printf("R: %d, G: %d, B: %d\n", r, g, b);
}

void print_grid(char **grid)
{
	int i = 0;

	if (!grid)
	{
		printf("(grid is NULL)\n");
		return;
	}
	while (grid[i])
	{
		printf("[%d] \"%s\"\n", i, grid[i]);
		i++;
	}
}
