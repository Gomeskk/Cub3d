/* ************************************************************************** */
/*                                                                            */
/*   test_menu.c - Test menu initialization and image loading                */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <stdio.h>


/* tor run for testing : 
cd /home/gomes/Cub3d
cc -Wall -Wextra -Werror -o test_menu src/menu/test_menu.c src/menu/menu_state.c src/menu/menu_images.c src/menu/menu_images_arrays.c src/menu/menu_navigation.c src/menu/menu_navigation_options.c src/menu/menu_resolution.c src/menu/menu_input.c src/menu/menu_render.c src/menu/menu_utils.c src/menu/menu_transparency.c -I./inc -I./complete_lib/minilibx-linux complete_lib/minilibx-linux/libmlx.a -L./complete_lib/42_Libft -lft -lXext -lX11 -lm

  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=mlx.supp ./test_menu
 */
int	close_window(t_cub3d *data)
{
	cleanup_menu(data);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	main(void)
{
	t_cub3d	data;

	ft_memset(&data, 0, sizeof(t_cub3d));
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	data.current_width = WIDTH;
	data.current_height = HEIGHT;
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Menu Test"); // Create window
	if (!data.window)
	{
		printf("Error: Failed to create window\n");
		free(data.mlx);
		return (1);
	}
	printf("Loading menu images...\n");
	if (init_menu_images(&data) == -1)
	{
		printf("Error: Failed to load menu images\n");
		mlx_destroy_window(data.mlx, data.window);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	printf("✓ Menu images loaded successfully!\n");
	init_menu_state(&data);// Initialize menu state
	printf("✓ Menu state initialized\n");
	printf("  - menu_choice: %d\n", data.menu.menu_choice);
	printf("  - difficulty_choice: %d\n", data.menu.difficulty_choice);
	printf("  - sensibility_level: %d\n", data.menu.options.sensibility_level);
	printf("  - status: %d (MAIN_MENU_SCREEN=%d)\n", data.status, MAIN_MENU_SCREEN);
	printf("\nDisplaying menu (use UP/DOWN or W/S to navigate)...\n");
	render_main_menu(&data);
	printf("✓ Menu rendered\n");
	printf("  - Image dimensions: %dx%d\n",
		data.menu.screens.start_normal.width, data.menu.screens.start_normal.height);
	mlx_hook(data.window, 17, 0, close_window, &data);
	mlx_hook(data.window, 2, 1L<<0, key_press_handler, &data);
	mlx_hook(data.window, 3, 1L<<1, key_release_handler, &data);
	mlx_loop_hook(data.mlx, menu_loop_handler, &data);
	printf("\n=== Test Complete ===\n");
	printf("Controls:\n");
	printf("  UP/DOWN or W/S: Navigate menu\n");
	printf("  ENTER/SPACE: Select option\n");
	printf("  ESC: Exit\n\n");
	mlx_loop(data.mlx);// Start MLX loop
	return (0);
}
