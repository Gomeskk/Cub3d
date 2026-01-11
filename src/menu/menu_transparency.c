#include "../../inc/cub3d.h"

void	pixel_put(t_menu_img *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || y < 0 || y >= img->height || x >= img->width)
		return ;
	offset = (img->bpp >> 3);
	pixel = img->data + (y * img->size_line + x * offset);
	*(unsigned int *)pixel = color;
}

void	put_img_to_img(t_menu_img *screen, t_menu_img img, int screen_x, int screen_y)
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
		dst_pixel = (int *)(screen->data + (screen_y + y) * screen->size_line + screen_x * pixel_offset);
		x = -1;
		while (++x < img.width)
		{
			if (screen_x + x >= 0 && screen_x + x < screen->width && src_pixel[x] >= 0)
				dst_pixel[x] = src_pixel[x];
		}
	}
}
