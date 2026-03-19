/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpires-r <bpires-r@student.42lisboa.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 21:47:36 by bpires-r          #+#    #+#             */
/*   Updated: 2026-03-19 21:47:36 by bpires-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../complete_lib/42_GNL/get_next_line_bonus.h"
# include "../complete_lib/42_Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <sys/time.h>
# include "menu.h"

typedef enum e_status
{
	MAIN_MENU_SCREEN,
	MENU_START,
	MENU_OPTIONS,
	MENU_CREDITS,
	DIFFICULTY_SCREEN,
	DIFF_EASY,
	DIFF_MEDIUM,
	DIFF_HARD,
	SKIN_SELECT,
	GAME,
	OPTIONS_SCREEN,
	CREDITS_SCREEN,
}				t_status;

typedef struct s_cub3d
{
	void			*mlx;
	void			*window;
	int				current_width;
	int				current_height;
	int				tile;
	int				enemy_frame_count;
	int				enemy_anim_enabled;
	double			*z_buffer;
	double			frame_dt;
	t_img			img;
	t_textures		textures;
	t_wall_textures	wall_textures;
	t_img			enemy_texture;
	t_img			enemy_frames[ENEMY_ANIM_FRAMES];
	t_hands			hands;
	t_status		status;
	t_tiles			tiles;
	t_map			map;
	t_player		player;
	t_keys			keys;
	t_mouse			mouse;
	t_menu			menu;
	t_game_settings	game_settings;
	t_ray			ray;
	t_fps_counter	fps;
}					t_cub3d;

//			INIT			//
void			init_data(t_cub3d *data);
void			init_game(t_cub3d *data);
int				load_enemy_animations(t_cub3d *data);
void			init_player_direction_ns(t_cub3d *data, char spawn);
void			init_player_direction_ew(t_cub3d *data, char spawn);
void			init_enemy_runtime_state(t_cub3d *data);
int				load_hands_textures(t_cub3d *data);
void			render_hands(t_cub3d *data);

//			PARSER			//
int				parse_map(t_cub3d *data);
int				parse_texture(char *s, char **dest);
int				parse_colour(char *s, int *dest, t_cub3d *data);
int				parse_identifiers(t_cub3d *data);

int				check_map_name(char *map);
void			check_spawn(t_cub3d *data, char c, int x, int y);
int				is_closed(t_cub3d *data);
void			indetifier_checker(t_cub3d *data);

//			MOUSE ROTATE 	//
int				mouse_moved(int x, int y, t_cub3d *data);
void			update_mouse_rotation(t_cub3d *data, double dt);
void			update_mouse_rotation(t_cub3d *data, double dt);

//			KEYBOARD ROTATE //
void			update_keyboard_rotation(t_cub3d *data, double dt);

//        RAYCASTER		    //
void			raycast_render(t_cub3d *data);
void			apply_flashlight(t_cub3d *data);
void			init_ray(t_cub3d *data, t_ray *ray, int screen_x);
void			setup_dda(t_cub3d *data, t_ray *ray);
void			perform_dda(t_cub3d *data, t_ray *ray);
void			draw_wall_column(t_cub3d *data, t_ray *ray, int x);

//			UTILS			//
int				is_ident_line(char *line);
int				is_empty_line(const char *s);
void			skip_sp_tb(char *s, int *i);
int				get_tile_size(t_cub3d *data);
double			get_time_in_seconds(void);
double			get_delta_time(void);
void			clear_image(t_img *img, int color);
void			draw_screen_border(t_cub3d *data);

//			FPS COUNTER		//
void			init_fps_counter(t_fps_counter *fps);
void			update_fps_counter(t_fps_counter *fps);
void			render_fps(t_cub3d *data);

//			MAP UTILS		//
int				count_lines(char *map);
int				read_map(char *map, t_cub3d *data);
void			copy_line(char **dest, char *src, int max_x);
char			**build_grid(t_cub3d *data);
int				is_map_line(char c);
int				has_space_neighbor(char **g, int r, int c);

//			2DGAME			//
void			pixel_put(t_img *img, int x, int y, int color);
void			draw_minimap(t_cub3d *data);
void			render_minimap(t_cub3d *data);
void			draw_direction_line(t_img *img, t_cub3d *data, int color);
void			put_color_tile(t_img *screen, int pos[2], int color, int tile);
void			calc_movement_direction(t_cub3d *data, double *dx,
					double *dy);

//			MINIMAP			//
void			draw_map_tiles(t_cub3d *data, int params[2]);
double			minimap_ray_dist(t_cub3d *data, double ray_dx, double ray_dy);
void			draw_player_on_map(t_cub3d *data, int params[3]);

//			RAYCASTING			//
void			raycast_render(t_cub3d *data);
void			init_ray(t_cub3d *data, t_ray *ray, int screen_x);
void			setup_dda(t_cub3d *data, t_ray *ray);
void			perform_dda(t_cub3d *data, t_ray *ray);
void			draw_wall_column(t_cub3d *data, t_ray *ray, int x);

//			GAME LOOP			//
void			game_start(t_cub3d *data);
void			reattach_hooks(t_cub3d *data);
int				unified_key_press(int keycode, t_cub3d *data);
int				unified_key_release(int keycode, t_cub3d *data);
int				unified_loop(t_cub3d *data);
void			handle_game_toggles(t_cub3d *data);
void			render_game_frame(t_cub3d *data, double delta_time);
int				render_game(t_cub3d *data);

//			COLLISION			//
int				circle_collides_wall(t_cub3d *data, double cx, double cy);
int				check_collision_range(t_cub3d *data,
					t_circle_center center, int start_row, int end_row);
int				row_has_collision(t_cub3d *data, t_circle_center center,
					int row, int *col_range);
void			get_col_range(t_cub3d *data, t_circle_center center,
					int *col_range);
int				is_blocking_cell(t_cub3d *data, int row, int col);
int				circle_intersects_rectangle(t_cub3d *data,
					t_circle_center center, int row, int col);	
void			player_movement(t_cub3d *data, double dt);
void			player_jump(t_cub3d *data, double dt);
void			cycle_fov(t_cub3d *data);
void			put_player_dot(t_img *img, int cx, int cy, int color);
int				key_released(int keycode, t_cub3d *data);
int				key_pressed(int keycode, t_cub3d *data);

//			TEXTURES			//
int				load_wall_textures(t_cub3d *data);
void			draw_textured_wall(t_cub3d *data, t_ray *ray, int x);
int				get_texture_pixel(t_img *texture, int x, int y);
int				get_tex_x(t_img *texture, double wall_x, t_ray *ray);
void			init_texture_step(t_img *texture, t_ray *ray,
					t_cub3d *data, t_tex_draw *td);
void			draw_texture_column(t_cub3d *data, t_tex_draw *td,
					t_img *texture, int x);
void			fill_wall_images(t_cub3d *data, void **images);

//			DOORS				//
void			init_doors(t_cub3d *data);
void			store_door_positions(t_cub3d *data);
int				is_door_open(t_cub3d *data, int x, int y);
void			toggle_door(t_cub3d *data);

//			BUTTONS				//
void			init_buttons(t_cub3d *data);
void			store_button_positions(t_cub3d *data);
int				is_button(t_cub3d *data, int x, int y);
void			activate_button(t_cub3d *data);

//			ENEMIES				//
void			init_enemies(t_cub3d *data);
void			store_enemy_positions(t_cub3d *data);
void			update_enemies(t_cub3d *data, double dt);
void			check_enemy_detection(t_cub3d *data);
int				check_enemy_collision(t_cub3d *data);
void			render_enemies(t_cub3d *data);
int				scan_patrol_min(t_cub3d *data, int grid_y, int grid_x);
int				scan_patrol_max(t_cub3d *data, int grid_y, int grid_x);
int				enemy_can_move(t_cub3d *data, double px, double py);
void			chase_player(t_cub3d *data, t_enemy *enemy, double dt);
void			patrol_enemy(t_cub3d *data, t_enemy *enemy, double dt);
int				bound_color(int value);
int				is_whiteish_pixel(int r, int g, int b);
int				is_blueish_pixel(int r, int g, int b);
int				apply_enemy_hue_gradient(int color, int stripe, int y,
					double anim_time);
void			calc_sprite_transform(t_cub3d *data, t_enemy *enemy,
					t_sprite_calc *sc);
void			calc_sprite_dims(t_cub3d *data, t_sprite_calc *sc);
void			sort_enemies_by_dist(t_cub3d *data, int *order, double *dist);

//			FREE/ERROR			//
void			free_all(t_cub3d *data);
void			exit_error(t_cub3d *data, char *message);
int				x_window(t_cub3d *data);
void			exit_game(char *end_game, t_cub3d *data);

#endif