#include "../../inc/cub3d.h"

void	pixel_put(t_menu_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || y >= img->height || x >= img->width)
		return ;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	put_img_to_img(t_menu_img *screen, t_menu_img img, int screen_x, int screen_y)
{
	int		x;
	int		y;
	char	*color;

	y = 0;
	while (y < img.height)
	{
		x = 0;
		while (x < img.width)
		{
			color = img.data + (y * img.size_line + x * (img.bpp / 8));
			if (*(int *)color >= 0)
				pixel_put(screen, screen_x + x, screen_y + y, *(int *)color);
			x++;
		}
		y++;
	}
}
