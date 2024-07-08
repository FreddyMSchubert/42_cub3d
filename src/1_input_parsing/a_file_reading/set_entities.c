/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:06:43 by freddy            #+#    #+#             */
/*   Updated: 2024/07/08 10:35:57 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_goal(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_trans){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						GOAL_NTT, get_texture_goal, tick_goal);
	return (true);
}

bool	set_health(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_trans){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
							HEALTH_NTT, get_texture_health, tick_health);
	return (true);
}

bool	set_blight(t_vec2 pos, t_tile_type ***map, char type)
{
	t_blight		*data;
	t_entity		*ntt;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_blight));
	if (!data)
		cub_exit("malloc failed", -1);
	if (type == 'q' || type == 'p')
		data->element = TYPE_WATER;
	else if (type == 'd' || type == 'o')
		data->element = TYPE_FIRE;
	else if (type == 'r' || type == 'i')
		data->element = TYPE_EARTH;
	else if (type == 's' || type == 'u')
		data->element = TYPE_AIR;
	data->state = BLIGHT_STATE_STANDING;
	data->hurt_state = -1;
	ntt = create_entity((t_trans){pos, {1.0, 0}}, \
							BLIGHT_NTT, get_texture_blight, tick_blight);
	ntt->on_collision = on_collision_blight;
	ntt->health = ENEMY_STARTING_HEALTH;
	data->drops_key = false;
	if (type == 'p' || type == 'o' || type == 'i' || type == 'u')
		data->drops_key = true;
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
	ntt = create_entity((t_trans){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						ORB_NTT, get_texture_orb, tick_orb);
	ntt->data = data;
	return (true);
}

bool	set_key(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_trans){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						KEY_NTT, get_texture_key, tick_key);
	return (true);
}
