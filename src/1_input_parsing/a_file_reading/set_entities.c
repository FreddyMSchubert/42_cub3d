/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:06:43 by freddy            #+#    #+#             */
/*   Updated: 2024/07/02 11:04:18 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_goal(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						GOAL_NTT, get_texture_goal, tick_goal);
	return (true);
}

bool	set_health(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
							HEALTH_NTT, get_texture_health, tick_health);
	return (true);
}

bool	set_blight(t_vec2 pos, t_tile_type ***map, char blight_type)
{
	t_blight		*data;
	t_entity		*ntt;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_blight));
	if (!data)
		cub_exit("malloc failed", -1);
	if (blight_type == 'q')
		data->element = TYPE_WATER;
	else if (blight_type == 'd')
		data->element = TYPE_FIRE;
	else if (blight_type == 'r')
		data->element = TYPE_EARTH;
	else if (blight_type == 's')
		data->element = TYPE_AIR;
	data->state = BLIGHT_STATE_STANDING;
	ntt = create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
							BLIGHT_NTT, get_texture_blight, tick_blight);
	ntt->on_collision = on_collision_blight;
	ntt->health = ENEMY_STARTING_HEALTH;
	ntt->data = data;
	return (true);
}

bool	set_orb(t_vec2 pos, t_tile_type ***map, char orb_type)
{
	t_orb			*data;
	t_entity		*ntt;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_orb));
	if (!data)
		cub_exit("malloc failed", -1);
	if (orb_type == 'w')
		data->element = TYPE_WATER;
	else if (orb_type == 'f')
		data->element = TYPE_FIRE;
	else if (orb_type == 'e')
		data->element = TYPE_EARTH;
	else if (orb_type == 'a')
		data->element = TYPE_AIR;
	ntt = create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						ORB_NTT, get_texture_orb, tick_orb);
	ntt->data = data;
	return (true);
}

bool	set_key(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						KEY_NTT, get_texture_key, tick_key);
	return (true);
}
