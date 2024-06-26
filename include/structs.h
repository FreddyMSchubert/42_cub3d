/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/26 13:47:49 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

// ---- UTILS

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_scale
{
	int	x;
	int	y;
}	t_scale;

// ---- GAME LOGIC

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_transform
{
	t_vec2	pos;
	t_vec2	rot;
}	t_transform;

typedef struct s_wall_scale
{
	int		x_left;
	int		x_right;
	int		height_left;
	int		height_right;
	char	direction;
}	t_wall_scale;

// ---- IMPORTANT

typedef enum e_tile_type
{
	VOID = -1,
	FLOOR = 0,
	WALL = 1
}	t_tile_type;

typedef struct s_input_data
{
	char		*no_texture_location;
	char		*so_texture_location;
	char		*we_texture_location;
	char		*ea_texture_location;
	char		*sprite_texture_location;
	t_color		floor_color;
	t_color		ceiling_color;
	t_tile_type	***map;
	t_transform	**walls;
}	t_input_data;

typedef struct s_persistent_data
{
	t_input_data	*input_data;
	mlx_t			*mlx;
	mlx_image_t		*background;
	mlx_image_t		*game_scene;
	mlx_image_t		*hud;
	mlx_image_t		*worldmap;
	bool			dirty;
	bool			**visible_walls;
	double			minimap_size;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	t_list			*entities;
	int32_t			prev_mouse_x;
	double			prev_time;
}	t_persistent_data;

// --- PLAYER

typedef struct s_inventory
{
	int	keys;
	int	water_orbs;
	int	fire_orbs;
	int	earth_orbs;
	int	air_orbs;
}	t_inventory;

typedef struct s_player
{
	t_transform	transform;
	t_transform	spawn_transform;

	t_inventory	inv;
}	t_player;

// ----- ENTITIES

typedef enum e_entity_type
{
	GOAL_E,
	DOOR_E,
	KEY_E,
	ORB_E
}	t_entity_type;

typedef struct s_entity	t_entity;
typedef struct s_entity
{
	t_entity_type	type;

	t_transform		transform;
	t_transform		spawn_transform;

	mlx_texture_t	*texture;
	bool			is_billboard;

	void			(*tick)(t_entity *self);

	void			*data;
}	t_entity;
// if is_billboard, the entity will always show its full face towards the player

// - DOOR

# define DOOR_STATE_CLOSED 0
# define DOOR_STATE_OPENING 1
# define DOOR_STATE_OPEN 2

# define DOOR_DIR_VERTICAL 0
# define DOOR_DIR_HORIZONTAL 1

typedef struct s_door
{
	int		state;
	bool	direction;
	t_vec2	open_pos;
	t_vec2	close_pos;
	double	door_open_progress;
}	t_door;

// - ORB

# define ORB_TYPE_WATER 0
# define ORB_TYPE_FIRE 1
# define ORB_TYPE_EARTH 2
# define ORB_TYPE_AIR 3

typedef struct s_orb
{
	int	type;
}	t_orb;

#endif