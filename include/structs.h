/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/24 11:08:21 by freddy           ###   ########.fr       */
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
	bool			dirty;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	t_list			*entities;
	int32_t			prev_mouse_x;
	double			prev_time;
}	t_persistent_data;

// ----- ENTITIES

typedef enum e_entity_type
{
	PLAYER_E,
	WALL_E
}	t_entity_type;

typedef struct s_entity
{
	t_entity_type	type;

	t_transform		transform;
	t_transform		spawn_transform;

	mlx_texture_t	*texture;
}	t_entity;

#endif