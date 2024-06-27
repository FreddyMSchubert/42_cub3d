/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:06:43 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 20:36:27 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_goal(t_vec2 pos, t_tile_type ***map)
{
	mlx_texture_t	*texture;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = game()->textures.star;
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0 , 0}}, GOAL_E, texture, true, tick_goal);
	return (true);
}

bool	set_blight(t_vec2 pos, t_tile_type ***map, char blight_type)
{
	mlx_texture_t	*texture;
	t_blight		*data;
	t_entity		*ntt;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = NULL;
	if (blight_type == 'r')
		texture = game()->textures.earth_blight_idle;
	else if (blight_type == 'q')
		texture = game()->textures.water_blight_idle;
	else if (blight_type == 'd')
		texture = game()->textures.fire_blight_idle;
	else if (blight_type == 's')
		texture = game()->textures.air_blight_idle;
	if (!texture)
		cub_exit("Failed to load blight texture!", -1);
	data = gc_malloc(sizeof(t_blight));
	if (blight_type == 'q')
		data->type = TYPE_WATER;
	else if (blight_type == 'd')
		data->type = TYPE_FIRE;
	else if (blight_type == 'r')
		data->type = TYPE_EARTH;
	else if (blight_type == 's')
		data->type = TYPE_AIR;
	data->state = BLIGHT_STATE_STANDING;
	ntt = create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0 , 0}}, BLIGHT_E, texture, true, tick_blight);
	ntt->on_collision = on_collision_blight;
	ntt->data = data;
	return (true);
}

bool	set_orb(t_vec2 pos, t_tile_type ***map, char orb_type)
{
	mlx_texture_t	*texture;
	t_orb			*data;
	t_entity		*ntt;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = NULL;
	if (orb_type == 'e')
		texture = game()->textures.earth_orb;
	else if (orb_type == 'f')
		texture = game()->textures.fire_orb;
	else if (orb_type == 'w')
		texture = game()->textures.water_orb;
	else if (orb_type == 'a')
		texture = game()->textures.air_orb;
	if (!texture)
		cub_exit("Failed to load orb texture!", -1);
	data = gc_malloc(sizeof(t_orb));
	if (orb_type == 'w')
		data->type = TYPE_WATER;
	else if (orb_type == 'f')
		data->type = TYPE_FIRE;
	else if (orb_type == 'e')
		data->type = TYPE_EARTH;
	else if (orb_type == 'a')
		data->type = TYPE_AIR;
	ntt = create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0 , 0}}, ORB_E, texture, true, tick_orb);
	ntt->data = data;
	return (true);
}

bool	set_key(t_vec2 pos, t_tile_type ***map)
{
	mlx_texture_t	*texture;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = game()->textures.key;
	if (!texture)
		cub_exit("Failed to load key texture!", -1);
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0 , 0}}, KEY_E, texture, true, tick_key);
	return (true);
}

bool	set_door(t_vec2 pos, t_tile_type ***map, char type)
{
	mlx_texture_t	*texture;
	t_door			*data;
	t_entity		*ntt;
	t_transform		trans;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = gc_malloc(sizeof(t_door));
	if (type == 'H')
		data->direction = DOOR_DIR_HORIZONTAL;
	else
		data->direction = DOOR_DIR_VERTICAL;
	texture = game()->textures.door;
	if (!texture)
		cub_exit("Failed to load door texture!", -1);
	trans.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	trans.rot = (t_vec2){0, 0};
	if (data->direction == DOOR_DIR_HORIZONTAL)
		trans.rot.x = 1;
	else
		trans.rot.y = 1;
	data->state = DOOR_STATE_CLOSED;
	ntt = create_entity(trans, DOOR_E, texture, false, tick_door);
	ntt->data = data;
	return (true);
}