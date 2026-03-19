/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:56:38 by bpires-r          #+#    #+#             */
/*   Updated: 2026/03/19 18:45:58 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//computes the 2D positional difference between an enemy sprite 
//and the player based on tile. It then calculates 
//the transformed sprite coordinates (tx and ty) using the
//inverse camera matrix, translating the sprite into the player's
//localized camera space for raycasting rendering.
void	calc_sprite_transform(t_cub3d *data, t_enemy *enemy,
	t_sprite_calc *sc)
{
	sc->sx = enemy->pos_x / data->tile - data->player.pos_x / data->tile;
	sc->sy = enemy->pos_y / data->tile - data->player.pos_y / data->tile;
	sc->inv = 1.0 / (data->player.plane_x * data->player.dir_y
			- data->player.dir_x * data->player.plane_y);
	sc->tx = sc->inv * (data->player.dir_y * sc->sx
			- data->player.dir_x * sc->sy);
	sc->ty = sc->inv * (-data->player.plane_y * sc->sx
			+ data->player.plane_x * sc->sy);
}

//calculates and sets the vertical drawing boundaries (start_y and end_y)
//for a sprite based on its height, the screen's height, and a 
//vertical offset derived from the player's pitch
static void	set_sprite_vertical_bounds(t_cub3d *data, t_sprite_calc *sc)
{
	sc->v_offset = (int)data->player.pitch + (int)data->player.z_offset;
	sc->start_y = -sc->height / 2 + data->current_height / 2 + sc->v_offset;
	if (sc->start_y < 0)
		sc->start_y = 0;
	sc->end_y = sc->height / 2 + data->current_height / 2 + sc->v_offset;
	if (sc->end_y >= data->current_height)
		sc->end_y = data->current_height - 1;
}

//calculates and sets the horizontal drawing boundaries (start_x and end_x)
//for a sprite based on its width and the screen's width
static void	set_sprite_horizontal_bounds(t_cub3d *data, t_sprite_calc *sc)
{
	sc->start_x = -sc->width / 2 + sc->screen_x;
	if (sc->start_x < 0)
		sc->start_x = 0;
	sc->end_x = sc->width / 2 + sc->screen_x;
	if (sc->end_x >= data->current_width)
		sc->end_x = data->current_width - 1;
}

//Calculates the on-screen dimensions and projection coordinates 
//for a sprite based on its transformed distance and the camera's field 
//of view. It also determines the vertical and horizontal draw bounds 
//by scaling the sprite relative to the screen size and camera plane
void	calc_sprite_dims(t_cub3d *data, t_sprite_calc *sc)
{
	double	plane_lenght;
	double	fov_scale;

	if (sc->ty <= 0.01)
	{
		sc->height = 0;
		return ;
	}
	plane_lenght = sqrt(data->player.plane_x * data->player.plane_x
			+ data->player.plane_y * data->player.plane_y);
	fov_scale = FOV_NORMAL / plane_lenght;
	sc->screen_x = (int)((data->current_width / 2)
			* (1 + sc->tx / sc->ty));
	sc->height = (int)(data->current_height / sc->ty * fov_scale);
	sc->width = sc->height;
	set_sprite_vertical_bounds(data, sc);
	set_sprite_horizontal_bounds(data, sc);
}
