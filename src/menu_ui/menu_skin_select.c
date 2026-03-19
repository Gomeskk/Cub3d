/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_skin_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joafaust <joafaust@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:25:41 by joafaust          #+#    #+#             */
/*   Updated: 2026/03/19 01:25:42 by joafaust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Copy one row of scaled t_img to menu with transparency
*/
static void	copy_timg_row(t_menu_img *screen, int *src_pix,
		t_scale_data data, int *dst_pix)
{
	int	x;
	int	src_x;

	x = -1;
	while (++x < data.scaled_w)
	{
		src_x = (int)(x / data.scale);
		if (data.screen_x + x >= 0 && data.screen_x + x < screen->width
			&& src_pix[src_x] >= 0)
			dst_pix[x] = src_pix[src_x];
	}
}

/*
** Convert and scale t_img (mlx image) to t_menu_img with transparency
** Used for displaying hand skins on menu screen
*/
void	put_timg_to_menu_scaled(t_menu_img *screen, t_img *img,
		t_scale_data data)
{
	int		y;
	int		src_y;
	int		draw_y;
	int		*src_pix;
	int		*dst_pix;

	data.scaled_w = (int)(img->width * data.scale);
	data.scaled_h = (int)(img->height * data.scale);
	y = -1;
	while (++y < data.scaled_h)
	{
		draw_y = data.screen_y + y;
		if (draw_y < 0 || draw_y >= screen->height)
			continue ;
		src_y = (int)(y / data.scale);
		src_pix = (int *)(img->data + src_y * img->size_line);
		dst_pix = (int *)(screen->data + draw_y * screen->size_line
				+ data.screen_x * (screen->bpp >> 3));
		copy_timg_row(screen, src_pix, data, dst_pix);
	}
}

/*
** Draw the selected hand skin on screen with proper centering
*/
void	draw_hand_skin(t_cub3d *data, float scale)
{
	t_img	*current_skin;
	float	skin_scale;
	int		skin_x;
	int		skin_y;

	current_skin = &data->hands.skins[data->menu.skin_choice];
	skin_scale = scale * 0.55;
	skin_x = (int)((data->current_width
				- current_skin->width * skin_scale) / 2);
	skin_y = (int)((data->current_height
				- current_skin->height * skin_scale) / 2 + (48 * scale));
	put_timg_to_menu_scaled(&data->menu.screens.screen_buffer,
		current_skin, init_scale_data(skin_x, skin_y, skin_scale));
}
