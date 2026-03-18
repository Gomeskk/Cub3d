/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hue_shift.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:57:13 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 22:57:14 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bound_color(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

int	is_whiteish_pixel(int r, int g, int b)
{
	int	min_c;
	int	max_c;

	min_c = r;
	if (g < min_c)
		min_c = g;
	if (b < min_c)
		min_c = b;
	max_c = r;
	if (g > max_c)
		max_c = g;
	if (b > max_c)
		max_c = b;
	if (min_c > 185 && (max_c - min_c) < 38)
		return (1);
	return (0);
}

int	is_blueish_pixel(int r, int g, int b)
{
	if (b > 85 && b > r + 18 && b > g + 10)
		return (1);
	return (0);
}

//0 = r 1= g 2 = b
int	apply_enemy_hue_gradient(int color, int stripe, int y,
	double anim_time)
{
	int		rgb[3];
	int		target_rgb[3];
	double	phase;
	double	mix;

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	if (is_whiteish_pixel(rgb[0], rgb[1], rgb[2]))
		return (color);
	if (!is_blueish_pixel(rgb[0], rgb[1], rgb[2]))
		return (color);
	phase = anim_time * 3.1 + stripe * 0.020 + y * 0.020;
	target_rgb[0] = (int)(4.0 + 14.0 * (sin(phase * 1.35 + 0.9) + 1.0) * 0.5);
	target_rgb[1] = (int)(110.0 + 80.0 * (sin(phase) + 1.0) * 0.5);
	target_rgb[2] = (int)(205.0 + 50.0 *(sin(phase * 1.35 + 0.9) + 1.0) * 0.5);
	mix = 0.36 + 0.38 * (sin(phase) + 1.0) * 0.5;
	rgb[0] = bound_color((int)(rgb[0] * (1.0 - mix) + target_rgb[0] * mix));
	rgb[1] = bound_color((int)(rgb[1] * (1.0 - mix) + target_rgb[1] * mix));
	rgb[2] = bound_color((int)(rgb[2] * (1.0 - mix) + target_rgb[2] * mix));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
