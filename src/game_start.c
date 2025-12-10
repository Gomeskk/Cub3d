/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:22:22 by bpires-r          #+#    #+#             */
/*   Updated: 2025/12/10 18:02:13 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double get_time_in_seconds(void)
{
    struct timespec ts;
    clock_gettime(1, &ts);
    return (ts.tv_sec + ts.tv_nsec / 1e9);
}

static double get_delta_time(void)
{
    static double last = 0.0;
    double now = get_time_in_seconds();

    if (last == 0.0) {
        last = now;
        return 0.0;
    }
    double dt = now - last;
    last = now;
    return dt;
}

static int	key_pressed(int keycode, t_cub3d *data)
{
	if (keycode == XK_Escape)
		x_window(data);
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = 1;
	return (0);
}


static int	key_released(int keycode, t_cub3d *data)
{
	if (keycode == XK_Up || keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_Left || keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_Down || keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_Right || keycode == XK_d)
		data->keys.d = 0;
	return (0);
}

static void	clear_image(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

static int	render_game(t_cub3d *data)
{
	static double	time;

	if (time >= 1.0 / FPS)
	{
		time += get_delta_time();
		draw_minimap(data);
		mlx_clear_window(data->mlx, data->window);
		mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
		time = 0;
	}
	return (0);
}

void	game_start(t_cub3d *data)
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUBO MUITO FIXE");
	data->img.image = mlx_new_image(data->mlx, 1920, 1080);
	data->img.data = mlx_get_data_addr(data->img.image, &data->img.bpp, &data->img.size_line, &data->img.type);
	data->img.width = 1920;
    data->img.height = 1080;
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
	mlx_hook(data->window, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->window, 3, 1L << 1, key_released, data);
	mlx_hook(data->window, 17, 0, x_window, data);
	mlx_loop_hook(data->mlx, render_game, data);
	mlx_loop(data->mlx);
	
}

int	get_tile_size(t_cub3d *data)
{
	int	size;

	if (data->map.row_count <= 0 || data->map.col_count <= 0)
		return (1);
	size = data->img.width / data->map.col_count;
	if (size > data->img.height / data->map.row_count)
		size = data->img.height / data->map.row_count;
	if (size < 1)
		size = 1;
	return (size);
}


void	draw_minimap(t_cub3d *data)
{
	int	x;
	int	y;
	int	color;
	int	tile = get_tile_size(data);

	clear_image(&data->img, 0x000000);
	y = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == '1') color = 0x444444;
			else if (data->map.grid[y][x] == ' ') color = 0x000000;
			else if (data->map.grid[y][x] == '0') color = 0xAAAAAA;
			else if (data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'S' 
				|| data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'W') color = 0xCC00FF;
			else
				color = 0x000000;
			put_color_tile(&data->img, x * tile, y * tile, color, tile);
			x++;
		}
		y++;
	}
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	
	if (x < 0 || y < 0 || y >= img->height || x >= img->width)
		return ;
	pixel = img->data + (y * img->size_line + (x * img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	put_color_tile(t_img *screen, int pos_x, int pos_y, int color, int tile)
{
	int		y;
	int		x;
	
	y = 0;
	while (y < tile)
	{
		x = 0;
		while (x < tile)
		{
			pixel_put(screen, pos_x + x, pos_y + y, color);
			x++;
		}
		y++;
	}
}
