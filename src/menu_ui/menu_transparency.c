#include "../../inc/cub3d.h"

// Bounds check to prevent segfault
// Convert bits per pixel to bytes: bpp >> 3 is bpp / 8
// Calculate pixel memory address
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

void	put_img_to_img(t_menu_img *screen, t_menu_img img, int screen_x, int screen_y)
{
	int		x;
	int		y;
	int		*src_pixel;
	int		*dst_pixel;
	int		pixel_offset;

	// Bytes per pixel for destination positioning
	pixel_offset = (img.bpp >> 3);
	y = -1;
	while (++y < img.height)
	{
		// Skip rows outside screen bounds
		if (screen_y + y < 0 || screen_y + y >= screen->height)
			continue ;
		// Get pointers to source and destination row
		src_pixel = (int *)(img.data + y * img.size_line);
		dst_pixel = (int *)(screen->data + (screen_y + y) * screen->size_line + screen_x * pixel_offset);
		x = -1;
		while (++x < img.width)
		{
			// TRANSPARENCY CHECK: src_pixel[x] >= 0 means opaque pixel
			// Negative values = transparent (don't draw)
			if (screen_x + x >= 0 && screen_x + x < screen->width && src_pixel[x] >= 0)
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
		int screen_x, int screen_y, t_scale_data data)
{
	int	x;
	int	src_x;
	int	*dst_pix;

	// Get destination row pointer
	dst_pix = (int *)(screen->data + screen_y * screen->size_line
			+ screen_x * (data.bpp >> 3));
	x = -1;
	while (++x < data.scaled_w)
	{
		// REVERSE MAPPING: find which source pixel maps to this destination
		// Divide by scale to map scaled coordinate back to original
		src_x = (int)(x / data.scale);
		// Copy with bounds check and transparency
		if (screen_x + x >= 0 && screen_x + x < screen->width
			&& src_pix[src_x] >= 0)
			dst_pix[x] = src_pix[src_x];
	}
}

/*
** Scale and copy image with transparency support
** SCALING PROCESS:
** 1. Calculate new dimensions (width * scale, height * scale)
** 2. For each destination row Y: find source row = Y / scale
** 3. For each destination pixel X: find source pixel = X / scale (in copy_scaled_row)
** This allows menu to adapt to different resolutions (960x540 up to 1920x1080)
*/
void	put_img_to_img_scaled(t_menu_img *screen, t_menu_img img,
		int screen_x, int screen_y, float scale)
{
	int			y;
	int			src_y;
	int			*src_pix;
	t_scale_data	data;

	// Precalculate scaled dimensions
	data.scale = scale;
	data.scaled_w = (int)(img.width * scale);
	data.scaled_h = (int)(img.height * scale);
	data.bpp = img.bpp;
	y = -1;
	while (++y < data.scaled_h)
	{
		// Skip rows outside screen
		if (screen_y + y < 0 || screen_y + y >= screen->height)
			continue ;
		// REVERSE MAP: find source row for this destination row
		src_y = (int)(y / scale);
		src_pix = (int *)(img.data + src_y * img.size_line);
		// Copy entire row with horizontal scaling
		copy_scaled_row(screen, src_pix, screen_x, screen_y + y, data);
	}
}
