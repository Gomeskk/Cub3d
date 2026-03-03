
#ifndef CUB3D_H
# define CUB3D_H

# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <X11/keysym.h>
# include "defines.h"
# include "structs.h"

/* typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img; */

typedef struct s_cub3d
{
	void			*mlx;
	void			*window;
	int				current_width;
	int				current_height;
	int				tile;
	t_img			img;
	t_textures		textures;
	t_wall_textures	wall_textures;
	t_status		status;
	t_tiles			tiles;
	t_map			map;
	t_player		player;
	t_keys			keys;
	t_mouse			mouse;
	t_menu			menu;
	t_game_settings	game_settings;
	t_ray			ray;
}					t_cub3d;

//			INIT			//
void    init_data(t_cub3d *data);
void	init_game(t_cub3d *data);

//			PARSER			//
int		parse_map(t_cub3d *data);
int		parse_texture(char *s, char **dest);
int		parse_colour(char *s, int *dest, t_cub3d *data);
int		parse_identifiers(t_cub3d *data);

int		check_map_name(char *map);
void	check_spawn(t_cub3d *data, char c, int x, int y);
int		is_closed(t_cub3d *data);
void	indetifier_checker(t_cub3d *data);

//			MOUSE ROTATE 	//
int		mouse_moved(int x, int y, t_cub3d *data);
void	update_mouse_rotation(t_cub3d *data, double dt);
void	update_mouse_rotation(t_cub3d *data, double dt);

//			KEYBOARD ROTATE //
void	update_keyboard_rotation(t_cub3d *data, double dt);

//        RAYCASTER		    //
void	raycast_render(t_cub3d *data);
void	init_ray(t_cub3d *data, t_ray *ray, int screen_x);
void	setup_dda(t_cub3d *data, t_ray *ray);
void	perform_dda(t_cub3d *data, t_ray *ray);
void	draw_wall_column(t_cub3d *data, t_ray *ray, int x);

//			UTILS			//
int		is_ident_line(char *line);
int 	is_empty_line(const char *s);
void	skip_sp_tb(char *s, int *i);
int		get_tile_size(t_cub3d *data);
double	get_time_in_seconds(void);
double	get_delta_time(void);
void	clear_image(t_img *img, int color);

//			MAP UTILS		//
int		count_lines(char *map);
int		read_map(char *map, t_cub3d *data);
void	copy_line(char **dest, char *src, int max_x);
char	**build_grid(t_cub3d *data);
int		is_map_line(char c);
int 	has_space_neighbor(char **g, int r, int c);

//			2DGAME			//
void	pixel_put(t_img *img, int x, int y, int color);
void	draw_minimap(t_cub3d *data);
void	draw_direction_line(t_img *img, t_cub3d *data, int color);
void	put_color_tile(t_img *screen, int pos_x, int pos_y, int color, int tile);

//			RAYCASTING			//
void	raycast_render(t_cub3d *data);
void	init_ray(t_cub3d *data, t_ray *ray, int screen_x);
void	setup_dda(t_cub3d *data, t_ray *ray);
void	perform_dda(t_cub3d *data, t_ray *ray);
void	draw_wall_column(t_cub3d *data, t_ray *ray, int x);
void	game_start(t_cub3d *data);
void	run_with_menu(t_cub3d *data); // adicionei
void	reattach_hooks(t_cub3d *data); //size scale resolution of the game // adicionei
int		circle_collides_wall(t_cub3d *data, double cx, double cy);
void    player_movement(t_cub3d *data, double dt);
void	player_jump(t_cub3d *data, double dt);
void	cycle_fov(t_cub3d *data);
void	put_player_dot(t_img *img, int cx, int cy, int radius, int color);
int		key_released(int keycode, t_cub3d *data);
int		key_pressed(int keycode, t_cub3d *data);

//			TEXTURES			//
int		load_wall_textures(t_cub3d *data);
void	draw_textured_wall(t_cub3d *data, t_ray *ray, int x);
int		get_texture_pixel(t_img *texture, int x, int y);
int		get_tex_x(t_img *texture, double wall_x, t_ray *ray);
void	init_texture_step(t_img *texture, t_ray *ray,
			t_cub3d *data, t_tex_draw *td);
void	draw_texture_column(t_cub3d *data, t_tex_draw *td,
			t_img *texture, int x);

//			FREE/ERROR			//
void	free_all(t_cub3d *data);
void	exit_error(t_cub3d *data, char *message);
int		x_window(t_cub3d *data);
void	exit_game(char *end_game, t_cub3d *data);

//			MENU			//
// menu_state.c
int		init_menu_images(t_cub3d *data);
void	init_menu_state(t_cub3d *data);
void	cleanup_menu(t_cub3d *data);
// menu_images.c
int		load_xpm_with_data(void *mlx, t_menu_img *img, char *path);
int		init_start_game_images(t_cub3d *data);
int		init_difficulty_images(t_cub3d *data);
int		init_options_images(t_cub3d *data);
// menu_images_arrays.c
int		load_image_array(void *mlx, t_menu_img *imgs,
			const char **paths, int count);
int		init_volume_images(t_cub3d *data);
int		init_sensibility_images(t_cub3d *data);
int		init_resolution_images(t_cub3d *data);
// menu_navigation.c
int		handle_main_menu_keys(int keycode, t_cub3d *data);
int		handle_difficulty_keys(int keycode, t_cub3d *data);
int		handle_credits_keys(int keycode, t_cub3d *data);
int		menu_key_handler(int keycode, t_cub3d *data);
// menu_navigation_options.c
void	adjust_setting(t_cub3d *data, int direction);
void	handle_horizontal_keys(int keycode, t_cub3d *data);
int		set_arrow_direction(t_cub3d *data, int direction);
void	apply_resolution_change(t_cub3d *data, int dir, int threshold);
void	handle_vertical_keys(int keycode, t_cub3d *data);
void	handle_enter_key(t_cub3d *data);
// menu_resolution.c
void	apply_resolution(t_cub3d *data, int new_level);
// menu_utils.c
double	get_sensibility_multiplier(int level);
// menu_input.c
int		key_press_handler(int keycode, t_cub3d *data);
int		key_release_handler(int keycode, t_cub3d *data);
int		menu_loop_handler(t_cub3d *data);
// menu_render.c
void	render_main_menu(t_cub3d *data);
void	render_difficulty_menu(t_cub3d *data);
void	render_credits(t_cub3d *data);
void	pixel_put_menu(t_menu_img *img, int x, int y, int color);
void	put_img_to_img(t_menu_img *screen, t_menu_img img, int screen_x, int screen_y);
void	put_img_to_img_scaled(t_menu_img *screen, t_menu_img img,
			int screen_x, int screen_y, float scale);

//			TESTER				//
void	print_rgb(int color);
void 	print_grid(char **grid);

#endif