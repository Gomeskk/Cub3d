/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:31:08 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/18 23:39:04 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_hand_paths(char *paths[HAND_SKIN_COUNT])
{
	paths[0] = "Png_images/Hands/light1.xpm";
	paths[1] = "Png_images/Hands/light2.xpm";
	paths[2] = "Png_images/Hands/light3.xpm";
	paths[3] = "Png_images/Hands/medium1.xpm";
	paths[4] = "Png_images/Hands/medium2.xpm";
	paths[5] = "Png_images/Hands/medium3.xpm";
	paths[6] = "Png_images/Hands/dark1.xpm";
	paths[7] = "Png_images/Hands/dark2.xpm";
	paths[8] = "Png_images/Hands/dark3.xpm";
}

static int	load_hand_skin(t_cub3d *data, t_img *skin, char *path)
{
	skin->image = mlx_xpm_file_to_image(data->mlx, path,
			&skin->width, &skin->height);
	if (!skin->image)
		return (0);
	skin->data = mlx_get_data_addr(skin->image, &skin->bpp,
			&skin->size_line, &skin->type);
	if (!skin->data)
		return (0);
	return (1);
}

int	load_hands_textures(t_cub3d *data)
{
	char	*paths[HAND_SKIN_COUNT];
	int		skin;

	set_hand_paths(paths);
	skin = 0;
	while (skin < HAND_SKIN_COUNT)
	{
		if (!load_hand_skin(data, &data->hands.skins[skin], paths[skin]))
			return (0);
		skin++;
	}
	data->hands.anim_phase = 0.0;
	return (1);
}
