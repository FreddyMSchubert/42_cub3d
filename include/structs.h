/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/01 21:45:16 by freddy           ###   ########.fr       */
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

typedef struct s_range
{
	int	min;
	int	max;
}	t_range;

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
	int			map_width;
	int			map_height;
	t_transform	**walls;
}	t_input_data;

typedef struct s_animation
{
	mlx_texture_t	*frame1;
	mlx_texture_t	*frame2;
	mlx_texture_t	*frame3;
}	t_animation;

typedef struct s_textures
{
	mlx_texture_t	*door;
	mlx_texture_t	*key;
	mlx_texture_t	*goal;
	mlx_texture_t	*health;

	mlx_texture_t	*heart_full;
	mlx_texture_t	*heart_half;

	mlx_texture_t	*water_orb;
	mlx_texture_t	*fire_orb;
	mlx_texture_t	*earth_orb;
	mlx_texture_t	*air_orb;

	mlx_texture_t	*air_blight_idle;
	t_animation		air_blight_death;
	t_animation		air_blight_attack;
	mlx_texture_t	*fire_blight_idle;
	t_animation		fire_blight_death;
	t_animation		fire_blight_attack;
	mlx_texture_t	*water_blight_idle;
	t_animation		water_blight_death;
	t_animation		water_blight_attack;
	mlx_texture_t	*earth_blight_idle;
	t_animation		earth_blight_death;
	t_animation		earth_blight_attack;
}	t_textures;

typedef struct s_persistent_data
{
	t_input_data	*input_data;
	mlx_t			*mlx;
	mlx_image_t		*background;
	mlx_image_t		*game_scene;
	mlx_image_t		*hud;
	bool			**visible_walls;
	double			minimap_size;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	t_list			*entities;
	int32_t			prev_mouse_x;
	double			prev_time;
	t_textures		textures;
}	t_persistent_data;

// --- PLAYER

typedef struct s_inventory
{
	int			num_available_items;
	int			current_index;

	int			keys;
	int			water_orbs;
	int			fire_orbs;
	int			earth_orbs;
	int			air_orbs;

	mlx_image_t	*text_amount_key;
	mlx_image_t	*text_amount_water;
	mlx_image_t	*text_amount_fire;
	mlx_image_t	*text_amount_earth;
	mlx_image_t	*text_amount_air;
}	t_inventory;

typedef struct s_player
{
	t_transform	transform;
	t_transform	spawn_transform;

	int			element;

	int			health;

	t_inventory	inv;
}	t_player;

// ----- ENTITIES

typedef enum e_entity_type
{
	GOAL_NTT,
	DOOR_NTT,
	KEY_NTT,
	ORB_NTT,
	PROJECTILE_NTT,
	BLIGHT_NTT,
	HEALTH_NTT
}	t_entity_type;

typedef struct s_entity	t_entity;
typedef struct s_entity
{
	t_entity_type	type;
	unsigned int	id;
	bool			to_be_deleted;

	t_transform		transform;
	t_transform		spawn_transform;

	int				health;

	mlx_texture_t	*(*get_texture)(t_entity *self);
	bool			is_billboard;
	unsigned int	frames_since_state_change;

	void			(*tick)(t_entity *self);
	void			(*on_collision)(t_entity *self, t_entity *collider);

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

typedef struct s_orb
{
	int	element;
}	t_orb;

// - PROJECTILE

typedef struct s_projectile
{
	int	element;
}	t_projectile;

// - BLIGHT

# define BLIGHT_STATE_WALKING 0
# define BLIGHT_STATE_ATTACKING 1
# define BLIGHT_STATE_STANDING 2
# define BLIGHT_STATE_DYING 3

typedef struct s_blight
{
	int	element;
	int	state;
}	t_blight;

#endif