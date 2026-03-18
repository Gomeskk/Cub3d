#include "cub3d.h"

static void	set_hand_paths(char *paths[HAND_SKIN_COUNT])
{
	paths[0] = "Png_images/Hands/light1.xpm";
	paths[1] = "Png_images/Hands/medium1.xpm";
	paths[2] = "Png_images/Hands/dark1.xpm";
	paths[3] = "Png_images/Hands/light2.xpm";
	paths[4] = "Png_images/Hands/medium2.xpm";
	paths[5] = "Png_images/Hands/dark2.xpm";
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
	int		x;
	int		y;
	int		dst_y;
	int		*src_row;
	int		*dst_row;

	y = 0;
	while (y < dst->height)
	{
		dst_y = y + y_offset;
		if (dst_y < 0 || dst_y >= dst->height)
		{
			y++;
			continue ;
		}
		src_row = (int *)(src->data + (y * src->height / dst->height)
				* src->size_line);
		dst_row = (int *)(dst->data + dst_y * dst->size_line);
		x = 0;
		while (x < dst->width)
		{
			if (src_row[x * src->width / dst->width] >= 0)
				dst_row[x] = src_row[x * src->width / dst->width];
			x++;
		}
		y++;
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
