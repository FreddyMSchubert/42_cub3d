/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:06:43 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 15:55:13 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_goal(t_vec2 pos, t_tile_type ***map)
{
	mlx_texture_t	*texture;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = mlx_load_png("./assets/entities/star.png");
	if (!texture)
		cub_exit("Failed to load goal texture!", -1);
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
		texture = mlx_load_png("./assets/entities/blights/earth_blight.png");
	else if (blight_type == 'q')
		texture = mlx_load_png("./assets/entities/blights/water_blight.png");
	else if (blight_type == 'd')
		texture = mlx_load_png("./assets/entities/blights/fire_blight.png");
	else if (blight_type == 's')
		texture = mlx_load_png("./assets/entities/blights/air_blight.png");
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
		texture = mlx_load_png("./assets/entities/orbs/earth_orb.png");
	else if (orb_type == 'f')
		texture = mlx_load_png("./assets/entities/orbs/fire_orb.png");
	else if (orb_type == 'w')
		texture = mlx_load_png("./assets/entities/orbs/water_orb.png");
	else if (orb_type == 'a')
		texture = mlx_load_png("./assets/entities/orbs/air_orb.png");
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
	texture = mlx_load_png("./assets/entities/key.png");
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
	texture = mlx_load_png("./assets/entities/door.png");
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