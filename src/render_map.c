
#include "cub3d.h"

static void	draw_tile_at(t_cub3d *game, int tile_col, int tile_row, int color)
{
	int	local_x;
	int	local_y;
	int	pixel_x;
	int	pixel_y;

	local_x = 0;
	while (local_x < TILE_SIZE)
	{
		local_y = 0;
		while (local_y < TILE_SIZE)
		{
			pixel_x = tile_col * TILE_SIZE + local_x;
			pixel_y = tile_row * TILE_SIZE + local_y;
			if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0
				&& pixel_y < HEIGHT)
				mlx_pixel_put(game->mlx, game->window, pixel_x, pixel_y, color);
			local_y++;
		}
		local_x++;
	}
}

void	render_walls(t_cub3d *game)
{
	int		map_row;
	int		map_col;
	char	cell;

	map_row = 0;
	while (map_row < game->map.row_count)
	{
		map_col = 0;
		while (game->map.map[map_row][map_col]
			&& game->map.map[map_row][map_col] != '\n')
		{
			cell = game->map.map[map_row][map_col];
			if (cell == '1')
				draw_tile_at(game, map_col, map_row, 0x00FFFFFF);
			map_col++;
		}
		map_row++;
	}
}

// future reference maybe, changing the mlx_pixel_put to 
//mlx_new_image + mlx_get_data_addr to draw faster