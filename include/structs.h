/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:38 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/21 08:58:40 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// ---- UTILS

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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

// ---- IMPORTANT

typedef struct s_input_data
{
	char		*no_texture_location;
	char		*so_texture_location;
	char		*we_texture_location;
	char		*ea_texture_location;
	t_color		floor_color;
	t_color		ceiling_color;
	t_transform	**walls;
}	t_input_data;

typedef struct s_input_data_step_one
{
	t_input_data	*data;
	char			**map;
}	t_input_data_step_one;

// ----- CURRENTLY UNUSED

typedef enum e_entity_type
{
	PLAYER,
	ENEMY,
	ITEM,
	PROJECTILE
}	t_entity_type;

typedef struct s_entity
{
	t_entity_type	type;
	t_transform		transform;
}	t_entity;

#endif