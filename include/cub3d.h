/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:47 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/24 11:14:28 by freddy           ###   ########.fr       */
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
# include <float.h>


/* ---- SETTINGS ---- */
# define MAP_TILES " 10NESWG"

/* ----- LOGGER ----- */
# define LOGGER_ERROR 'e'
# define LOGGER_WARNING 'w'
# define LOGGER_INFO 'i'
# define LOGGER_STEP 's'

/* ----- EXIT CODES ----- */
# define EXIT_SUCCESS 0
# define EXIT_INVALID_ARGS 1
# define EXIT_INVALID_FILE_EXTENSION 2
# define EXIT_MAP_ERROR 3

/* ---- FUNCTIONS ----- */
// lets mirror the file system in here. the less ---, the deeper the file

// ----- general
t_persistent_data	*game(void);
t_list				**gc(void);
t_entity			*player(void);

// ----- 1_input_parsing
void				parse_input(char	*filepath);
// file helper
int					get_file_length(char *filename);
bool				check_player(bool *invalid);
// parse
bool				set_values(char **split, t_input_data **input_data, char **data, int *i);
bool				parse_attributes(char **data, t_input_data **input_data, int *i);
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
// squarify map
void				squarify_map(void);
// util
bool				free_split(char	**split, bool ret);
int					split_len(char **split);
bool				char_is_in(char c, char *seq);
bool				regex(char *line, char *reg);

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
void				handle_mouse_mv(void);
void				key_hook(mlx_key_data_t keydata, void *param);
void				handle_player_move(void);
// util
void				turn(double amount);
// --- b_rendering
void				render_game_scene(void);
void				do_wall_operations();
// raycasting util
double				pos_distance(t_vec2 pos1, t_vec2 pos2);
t_vec2				scale_vector(t_vec2 t1, double distance);
t_vec2				raycast_intersect(t_transform t1, t_transform t2);
t_vec2				get_wall_intersection(t_transform **walls, t_transform ray);
t_vec2				get_entity_intersection(t_list *entities, t_transform ray, \
										t_entity **closest_entity);
// - 1 raycast walls
void				raycast_walls(void);
// - 2 calc walls
void				calc_wall(int ray_index, t_vec2 intersect);
void				calc_entity(int ray_index, t_vec2 intersect, t_entity *ntt);
// - 3 draw walls
void				draw_gameobject(int start_x, int end_x, int height, mlx_texture_t *tex, double hit_offset);
// - util
bool				get_wall_orientation(t_vec2 intersect);		// d
char				get_wall_face_to_render(t_vec2 intersect);	// wall_orientation
t_transform			get_wall_from_intersect(t_vec2 intersect);

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
void				gc_exit_error(void);

// logging
void				logger(char type, char *message);
void				logger_verbose(char type, char *message);
// printing
void				print_map(t_tile_type ***map, char *mode);
void				print_walls(void);

// general
void				cub_exit_error(char	*message);

// colors
unsigned int		t_color_to_int(t_color color);
t_color				int_to_t_color(int color);
void				log_color_from_t_color(t_color color);
void				log_color_from_int(int color);
int					rgba_to_int(int r, int g, int b, int a);

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
t_transform			get_face_vector(t_transform *ntt_trans);

#endif