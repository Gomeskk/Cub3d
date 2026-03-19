#ifndef MENU_H
# define MENU_H

// menu_state.c
int				init_menu_images(t_cub3d *data);
void			init_menu_state(t_cub3d *data);
void			cleanup_menu(t_cub3d *data);
// menu_images.c
int				load_xpm_with_data(void *mlx, t_menu_img *img, char *path);
int				init_start_game_images(t_cub3d *data);
int				init_difficulty_images(t_cub3d *data);
int				init_skin_select_images(t_cub3d *data);
int				init_options_images(t_cub3d *data);
// menu_images_arrays.c
int				load_image_array(void *mlx, t_menu_img *imgs,
					const char **paths, int count);
int				init_volume_images(t_cub3d *data);
int				init_sensibility_images(t_cub3d *data);
int				init_resolution_images(t_cub3d *data);
// menu_navigation.c
int				handle_main_menu_keys(int keycode, t_cub3d *data);
int				handle_difficulty_keys(int keycode, t_cub3d *data);
int				handle_skin_select_keys(int keycode, t_cub3d *data);
int				handle_credits_screen_keys(int keycode, t_cub3d *data);
// menu_navigation_options.c
int				menu_key_handler(int keycode, t_cub3d *data);
void			handle_horizontal_keys(int keycode, t_cub3d *data);
void			handle_vertical_keys(int keycode, t_cub3d *data);
void			handle_enter_key(t_cub3d *data);
int				handle_options_screen_keys(int keycode, t_cub3d *data);
// menu_options_settings.c
void			adjust_setting(t_cub3d *data, int direction);
int				set_arrow_direction(t_cub3d *data, int direction);
void			apply_resolution_change(t_cub3d *data, int dir, int threshold);
// menu_resolution.c
void			apply_resolution(t_cub3d *data, int new_level);
// menu_resolution_init.c
int				create_new_window(t_cub3d *data, int width, int height);
int				create_menu_buffer(t_cub3d *data, int width, int height);
int				create_game_image(t_cub3d *data, int width, int height);
void			update_resol_settings(t_cub3d *data, int level, int w, int h);
// menu_utils.c
double			get_sensibility_multiplier(int level);
void			apply_difficulty_settings(t_cub3d *data);
// menu_input.c
int				key_press_handler(int keycode, t_cub3d *data);
int				key_release_handler(int keycode, t_cub3d *data);
int				menu_loop_handler(t_cub3d *data);
// menu_render.c
void			render_main_menu(t_cub3d *data);
void			render_difficulty_menu(t_cub3d *data);
void			render_skin_select(t_cub3d *data);
void			render_credits_screen(t_cub3d *data);
void			render_volume_sensibility(t_cub3d *data, float scale);
// menu_render_options.c
void			render_options_menu(t_cub3d *data);
void			pixel_put_menu(t_menu_img *img, int x, int y, int color);
void			put_img_to_img(t_menu_img *screen, t_menu_img img,
					int screen_x, int screen_y);
t_scale_data	init_scale_data(int screen_x, int screen_y, float scale);
void			put_img_to_img_scaled(t_menu_img *screen, t_menu_img img,
					t_scale_data data);
void			put_timg_to_menu_scaled(t_menu_img *screen, t_img *img,
					t_scale_data data);
void			draw_hand_skin(t_cub3d *data, float scale);

#endif