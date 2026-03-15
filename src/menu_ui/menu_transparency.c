#include "../../inc/cub3d.h"

/*
** Write one pixel into a menu image.
** It first checks bounds, then computes bytes-per-pixel and the destination
** memory address before writing the final color value.
*/
void	pixel_put_menu(t_menu_img *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0 || y >= img->height || x >= img->width)
		return ;
	offset = (img->bpp >> 3);
	pixel = img->data + (y * img->size_line + x * offset);
	*(unsigned int *)pixel = color;
}

/*
** Copy a source image into the screen image at (screen_x, screen_y).
** Rows outside screen bounds are skipped, and only non-negative source pixels
** are copied so transparent pixels are ignored.
*/
void	put_img_to_img(t_menu_img *screen,
		t_menu_img img, int screen_x, int screen_y)
{
	int		x;
	int		y;
	int		*src_pixel;
	int		*dst_pixel;
	int		pixel_offset;

	pixel_offset = (img.bpp >> 3);
	y = -1;
	while (++y < img.height)
	{
		if (screen_y + y < 0 || screen_y + y >= screen->height)
			continue ;
		src_pixel = (int *)(img.data + y * img.size_line);
		dst_pixel = (int *)(screen->data + (screen_y + y)
				* screen->size_line + screen_x * pixel_offset);
		x = -1;
		while (++x < img.width)
		{
			if (screen_x + x >= 0 && screen_x + x
				< screen->width && src_pixel[x] >= 0)
				dst_pixel[x] = src_pixel[x];
		}
	}
}

/*
** Copy one row of scaled image with transparency
** SCALING ALGORITHM: Maps destination pixel X to source pixel X
** Formula: src_x = dest_x / scale
** Example: scale=2.0, dest pixel 10 comes from source pixel 5
*/
static void	copy_scaled_row(t_menu_img *screen, int *src_pix,
		t_scale_data data)
{
	int	x;
	int	src_x;
	int	*dst_pix;

	dst_pix = (int *)(screen->data + data.screen_y * screen->size_line
			+ data.screen_x * (data.bpp >> 3));
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
** Initialize scaling parameters for menu image blitting.
*/
t_scale_data	init_scale_data(int screen_x, int screen_y, float scale)
{
	t_scale_data	data;

	data.scale = scale;
	data.screen_x = screen_x;
	data.screen_y = screen_y;
	data.scaled_w = 0;
	data.scaled_h = 0;
	data.bpp = 0;
	return (data);
}

/*
** Scale and copy image with transparency support
** SCALING PROCESS:
** 1. Calculate new dimensions (width * scale, height * scale)
** 2. For each destination row Y: find source row = Y / scale
** 3. For each destination pixel X: 
		find source pixel = X / scale (in copy_scaled_row)
** This allows menu to adapt to different resolutions (960x540 up to 1920x1080)
*/
void	put_img_to_img_scaled(t_menu_img *screen, t_menu_img img,
		t_scale_data data)
{
	int				y;
	int				src_y;
	int				*src_pix;
	int				draw_y;
	int				base_y;

	base_y = data.screen_y;
	data.scaled_w = (int)(img.width * data.scale);
	data.scaled_h = (int)(img.height * data.scale);
	data.bpp = img.bpp;
	y = -1;
	while (++y < data.scaled_h)
	{
		draw_y = base_y + y;
		if (draw_y < 0 || draw_y >= screen->height)
			continue ;
		src_y = (int)(y / data.scale);
		src_pix = (int *)(img.data + src_y * img.size_line);
		data.screen_y = draw_y;
		copy_scaled_row(screen, src_pix, data);
	}
}
