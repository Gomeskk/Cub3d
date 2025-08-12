
#include "cub3d.h"

static int	close_game(t_cub3d *game)
{
	free_map(&game->map);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

static int	handle_key(int keycode, t_cub3d *game)
{
	if (keycode == 65307) // ESC key in X11
		close_game(game);
	return (0);
}

int	main(void)
{
	t_cub3d	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.window = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d map");
	if (!game.window)
		return (1);
	if (load_map(&game.map, "maps/test_map.cub"))
		return (1);
	if (!validate_map(&game.map))
	{
		free_map(&game.map);
		return (1);
	}
	render_walls(&game);
	mlx_key_hook(game.window, handle_key, &game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

/* static int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == XK_Escape)
	{
		printf("ESC pressed, exiting.\n");
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_cub3d	game;

	printf("Starting cub3d debug...\n");
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		fprintf(stderr, "mlx_init() failed\n");
		return (1);
	}
	game.window = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d map debug");
	if (!game.window)
	{
		fprintf(stderr, "mlx_new_window() failed\n");
		return (1);
	}
	if (load_map(&game.map, "maps/test_map.cub"))
	{
		fprintf(stderr, "load_map() failed (check maps/test_map.cub path)\n");
		return (1);
	}
	printf("Map loaded: rows=%d cols=%d\n", game.map.row_count,
		game.map.col_count);
	if (!validate_map(&game.map))
	{
		fprintf(stderr,
			"validate_map() failed (map not rectangular or not enclosed)\n");
		free_map(&game.map);
		return (1);
	}
	printf("Map validated OK — rendering walls now.\n");
	render_walls(&game);
	mlx_key_hook(game.window, handle_key, &game);
	printf("Window should be visible. Press ESC to quit.\n");
	mlx_loop(game.mlx);
	free_map(&game.map);
	return (0);
} */