/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 19:19:31 by bpires-r          #+#    #+#             */
/*   Updated: 2026/01/04 21:05:45 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dd_algorithm(t_cub3d *data, int x, int y, int x2, int y2)
{
	int i = 1;
	float xinc;
	float yinc;
	int dx;
	int dy;
	int steps;

	dx = x2 - x;
	dy = y2 - y;

	if (abs(dx) >= abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;
	while (i <= steps)
	{
		pixel_put(&data->img, x, y, 0xFF0000);
		x += xinc;
		y += yinc;
		i++;
	}
}
