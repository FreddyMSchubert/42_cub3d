/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:47 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/01 16:33:52 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ----- INCLUDES ----- */
# include "../submodules/MLX42/include/MLX42/MLX42.h"
# include "../submodules/42_libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"

# include "colors.h"
# include "structs.h"
# include "settings.h"

// subject functions
# include <fcntl.h>    // open, close
# include <unistd.h>   // read, write, close
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <math.h>     // All functions of the math library (-lm)

// other
# include <stdbool.h>
# include <limits.h>

/* ---- SETTINGS ---- */
# define MAP_TILES " 10NESWGHVKwfeaqrdsh"
// ' ' -> VOID
// '1' -> WALL
// '0' -> FLOOR
// 'N' -> PLAYER LOOKING NORTH
// 'E' -> PLAYER LOOKING EAST
// 'S' -> PLAYER LOOKING SOUTH
// 'W' -> PLAYER LOOKING WEST
// 'G' -> GOAL
// 'H' -> HORIZONTAL DOOR
// 'V' -> VERTICAL DOOR
// 'K' -> KEY
// 'w' -> WATER ORB
// 'f' -> FIRE ORB
// 'e' -> EARTH ORB
// 'a' -> AIR ORB
// 'q' -> WATER BLIGHT
// 'd' -> FIRE BLIGHT
// 'r' -> EARTH BLIGHT
// 's' -> AIR BLIGHT
// 'h' -> HEALTH PICKUP

/* ----- LOGGER ----- */
# define LOGGER_ERROR 'e'
# define LOGGER_WARNING 'w'
# define LOGGER_INFO 'i'
# define LOGGER_STEP 's'
# define LOGGER_ACTION 'a'

/* ----- EXIT CODES ----- */
# define EXIT_SUCCESS 0
# define EXIT_INVALID_ARGS 1
# define EXIT_INVALID_FILE_EXTENSION 2
# define EXIT_MAP_ERROR 3

/* ----- ENTITY TPYES ----- */
# define TYPE_WATER 0
# define TYPE_FIRE 1
# define TYPE_AIR 2
# define TYPE_EARTH 3

/* ---- FUNCTIONS ----- */
// lets mirror the file system in here. the less ---, the deeper the file

// ----- general
t_persistent_data	*game(void);
t_list				**gc(void);
t_player			*player(void);

void				load_static_textures(void);

// ----- 0_map_generation
// mapmaker
void				generate_map(void);
// features
void				remove_walls(char **maze, int height, int width);
void				place_player_spawn(char **maze, t_scale	map_scale);
void				add_rooms(char **maze, t_scale scale, int room_count);
// file writer
void				write_cub_file(char **maze, int height, int width, \
										char *filename);
// entities
void				add_ntts_in_good_spots(char **maze, t_scale scale);
void				place_locked_goal(char **maze, t_scale	map_scale);
void				place_key(char **maze, t_scale scale);
// util
int					count_adjacent_walls(char **maze, t_scale pos, t_scale s);
void				print_mapmaker_map(char **maze, int height, int width);

// ----- 1_input_parsing
void				parse_input(char	*filepath);
// file helper
int					get_file_length(char *filename);
bool				check_player(bool *invalid);
// parse
bool				set_values(char **split, t_input_data **input_data, \
									char **data, int *i);
bool				parse_attributes(char **data, t_input_data **input_data, \
													int *i);
int					get_map_len(int *i, char **data);
t_tile_type			***make_map(int map_len, int *i, char **data);
bool				parse_map(char **data, t_input_data **input_data, int *i);
// read file
bool				basic_validate(t_input_data **in);
void				get_map_contents(char *filepath);
// set values
bool				set_entity_spawn(char dir, t_vec2 pos, t_tile_type ***map);
bool				set_value(char	**value, char	*set);
bool				set_color(t_color *color, char *color_val);
// create entities
bool				set_goal(t_vec2 pos, t_tile_type ***map);
bool				set_health(t_vec2 pos, t_tile_type ***map);
bool				set_orb(t_vec2 pos, t_tile_type ***map, char orb_type);
bool				set_blight(t_vec2 pos, t_tile_type ***map, \
										char blight_type);
bool				set_door(t_vec2 pos, t_tile_type ***map, char type);
bool				set_key(t_vec2 pos, t_tile_type ***map);
// squarify map
void				squarify_map(void);
// util
bool				free_split(char	**split, bool ret);
int					split_len(char **split);
bool				char_is_in(char c, char *seq);
bool				regex(char *line, char *reg);
void 				free_arr(void **arr);

// --- a_file_reading
void				get_map_contents(char *filepath);
// --- b_validation
void				validate(void);
// --- c_wall_conversion
void				convert_walls(void);
// util
t_scale				get_map_size(t_tile_type ***map);
t_transform			*create_transform(int x, int y, int rotx, int roty);
bool				wall_needed(t_tile_type ***map, int x, int y, t_scale size);

// ----- 2_setup
void				setup_mlx(void);
void				setup_player(void);

// ----- 3_game_loop
// --- a_game_logic
void				loop_hook(void *param);
void				cursor_hook(double x, double y, void *param);
void				handle_mouse_mv(void);
void				key_hook(mlx_key_data_t keydata, void *param);
void				scroll_hook(double xdelta, double ydelta, void *param);
void				mouse_click_hook(mouse_key_t button, action_t action, \
									modifier_key_t mods, void *param);
void				player_shoot(void);
// player movement
void				handle_player_move(void);
bool				is_position_valid(float x, float y);
// util
void				turn(double amount);
// --- b_rendering
void				render(void);
void				set_background(void);
// - hud
void				draw_crosshair(void);
void				draw_square(int x, int y, int size, int color);
void				draw_square_hud(int x, int y, int size, int color);
void				draw_square_world(int x, int y, int size, int color);
void				draw_inventory(void);
mlx_image_t			**get_amount_text_by_index(int index);
void				texture_draw(mlx_texture_t *texture, t_scale pos, \
										t_scale size);
void				cycle_inventory(int direction, bool direct);
int					*get_amount_of_item(int index);
int					get_tex_color_at(mlx_texture_t *tex, int x, int y);
int					get_minimap_opacity(int x, int y);
// minimap
void				hud_draw_minimap(void);
// - raycasting util
double				pos_dist(t_vec2 pos1, t_vec2 pos2);
t_vec2				scale_vector(t_vec2 t1, double distance);
t_vec2				raycast_intersect(t_transform t1, t_transform t2);
t_vec2				get_wall_intersection(t_transform **walls, t_transform ray);
t_vec2				*get_entity_intersection(t_transform ray, \
												t_entity ***entities);
// - 1 raycast walls
void				raycast_walls(void);
// - 2 calc walls
void				calc_wall(int ray_index, t_vec2 intersect);
void				calc_entity(int ray_index, t_vec2 intersect, t_entity *ntt);
// - 3 draw walls
void				draw_gameobject(int start_x, int end_x, int height, \
									mlx_texture_t *tex, double hit_offset);
void				set_pixel_color(mlx_image_t *img, int x, int y, int col);
// - util
bool				get_wall_orientation(t_vec2 intersect);
char				get_wall_face_to_render(t_vec2 intersect);
t_transform			get_wall_from_intersect(t_vec2 intersect);

// --- entities
void				tick_entities(void);
void				collide_entities(void);
// - player
void				on_collision_player(t_entity	*collider);
void				check_dead_player(void);
// - goal
void				tick_goal(t_entity *self);
mlx_texture_t		*get_texture_goal(t_entity *self);
// - door
void				tick_door(t_entity *self);
mlx_texture_t		*get_texture_door(t_entity *self);
// - health
void				tick_health(t_entity *self);
mlx_texture_t		*get_texture_health(t_entity *self);
// - key
void				tick_key(t_entity *self);
mlx_texture_t		*get_texture_key(t_entity *self);
// - orb
void				tick_orb(t_entity *self);
mlx_texture_t		*get_texture_orb(t_entity *self);
// - projectile
void				tick_projectile(t_entity *self);
void				shooooot(t_transform t, int type);
mlx_texture_t		*get_texture_projectile(t_entity *self);
// - blight
void				tick_blight(t_entity *self);
void				on_collision_blight(t_entity *self, t_entity *other);
mlx_texture_t		*get_texture_blight(t_entity *self);

# define WALL_ORIENTATION_HORIZONTAL 0
# define WALL_ORIENTATION_VERTICAL 1

# define WALL_FACE_NORTH 'N'
# define WALL_FACE_SOUTH 'S'
# define WALL_FACE_EAST 'E'
# define WALL_FACE_WEST 'W'

// ----- util
// garbage collector
t_list				*gc_create(void);
int					gc_append_element(void *content);
void				gc_cleanup_and_reinit(void);
void				*gc_malloc(size_t size);
void				gc_exit(int code);

// logging
void				logger(char type, char *message);
void				logger_verbose(char type, char *message);
// printing
void				print_map(t_tile_type ***map, char *mode);
void				print_walls(void);

// general
void				cub_exit(char *message, int code);

// colors
unsigned int		t_color_to_int(t_color color);
t_color				int_to_t_color(int color);
int					rgba_to_int(int r, int g, int b, int a);
t_color				with_opacity(t_color in, int opacity);

// positions
bool				is_same_wall(t_transform wall1, t_transform wall2);
t_vec2				sum_vectors(t_vec2 v1, t_vec2 v2);
char				get_color_for_wall(t_transform t);

// string
bool				str_is_equal(char *str1, char *str2);

// rotations
double				deg_to_rad(double degrees);
double				rad_to_deg(double radians);
t_vec2				deg_to_dir_vec(double degrees);
double				dir_vec_to_deg(t_vec2 dir);
double				normalize_degrees(double degrees);
t_vec2				rotate_vector_by_90_degrees(t_vec2 v, int direction);

// entities
t_transform			get_face_vector(t_entity *ntt);
t_entity			*create_entity(t_transform trans, t_entity_type type, \
		mlx_texture_t	*(*tex)(t_entity *self), void (*tick)(t_entity *self));
void				delete_entity(t_entity *self);

// vector
double				vec2_dot_product(t_vec2 a, t_vec2 b);
double				vec2_sqr_magnitude(t_vec2 v);
t_vec2				vec2_sub(t_vec2 a, t_vec2 b);

// random
double				random_val(void);
int					random_int(int min, int max);
void				init_random_seed(void);

// math
int					min(int a, int b);
int					max(int a, int b);

// blights
bool				a_beats_b(int a, int b);

#endif