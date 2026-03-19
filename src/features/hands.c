/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:57:07 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 23:31:26 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_hands_motion_offset(t_cub3d *data)
{
	double	speed;

	if (!data->keys.w && !data->keys.a && !data->keys.s && !data->keys.d)
	{
		data->hands.anim_phase = 0.0;
		return (0);
	}
	if (data->keys.shift && !data->keys.ctrl)
		speed = HAND_SPRINT_MOTION_SPEED;
	else
		speed = HAND_WALK_MOTION_SPEED;
	data->hands.anim_phase += data->frame_dt * speed;
	if (data->hands.anim_phase >= 2.0 * M_PI)
		data->hands.anim_phase = fmod(data->hands.anim_phase, 2.0 * M_PI);
	return ((int)(sin(data->hands.anim_phase) * HAND_MOTION_AMPLITUDE));
}

static void	draw_hands_scaled(t_img *dst, t_img *src, int y_offset)
{
	int		pos[2];
	int		*src_row;
	int		*dst_row;

	pos[0] = 0;
	while (pos[0] < dst->height)
	{
		if ((pos[0] + y_offset) < 0 || (pos[0] + y_offset) >= dst->height)
		{
			pos[0]++;
			continue ;
		}
		src_row = (int *)(src->data + (pos[0] * src->height / dst->height)
				* src->size_line);
		dst_row = (int *)(dst->data + (pos[0] + y_offset) * dst->size_line);
		pos[1] = 0;
		while (pos[1] < dst->width)
		{
			if (src_row[pos[1] * src->width / dst->width] >= 0)
				dst_row[pos[1]] = src_row[pos[1] * src->width / dst->width];
			pos[1]++;
		}
		pos[0]++;
	}
}

void	render_hands(t_cub3d *data)
{
	t_img	*skin_img;
	int		skin_idx;
	int		motion_offset;

	if (data->status != GAME)
		return ;
	motion_offset = get_hands_motion_offset(data);
	skin_idx = data->menu.skin_choice;
	if (skin_idx < 0 || skin_idx >= HAND_SKIN_COUNT)
		skin_idx = 0;
	skin_img = &data->hands.skins[skin_idx];
	if (!skin_img->image || !skin_img->data)
		return ;
	draw_hands_scaled(&data->img, skin_img, motion_offset);
}
