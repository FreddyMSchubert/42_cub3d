/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:03:47 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/08 13:00:08 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	init_door(t_door *data, char c)
{
	if (c == 'H' || c == '-')
		data->direction = DOOR_DIR_HORIZONTAL;
	else
		data->direction = DOOR_DIR_VERTICAL;
	data->type = DOOR_TYPE_LOCKED;
	if (c == '-' || c == '|')
		data->type = DOOR_TYPE_UNLOCKED;
	data->state = DOOR_STATE_CLOSED;
}

bool	set_door(t_vec2 pos, t_tile_type ***map, char c)
{
	t_door			*data;
	t_entity		*ntt;
	t_trans			trans;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_door));
	if (!data)
		cub_exit("malloc failed", -1);
	init_door(data, c);
	trans = (t_trans){(t_vec2){pos.x + 0.5, pos.y + 0.5}, (t_vec2){0, 0}};
	if (data->direction == DOOR_DIR_HORIZONTAL)
		trans.rot.x = 1;
	else
		trans.rot.y = 1;
	ntt = create_entity(trans, DOOR_NTT, get_texture_door, tick_door);
	ntt->is_billboard = false;
	data->idle_pos = trans.pos;
	ntt->data = data;
	return (true);
}

static inline void	init_elementor(t_elementor *data)
{
	data->stage = 1;
	data->animation_frame = 0;
	data->death_animation = -1;
	data->element1 = random_int(0, 3);
	data->element2 = random_int(0, 3);
	data->element3 = random_int(0, 3);
	data->mvmnt = ELEMENTOR_MVMNT_STAND;
	data->frames_since_element_switch = 0;
}

bool	set_boss(t_vec2 pos, t_tile_type ***map)
{
	t_elementor	*data;
	t_entity	*ntt;
	t_trans		trans;
	static int	count;

	if (++count > 1)
		cub_exit("Too many bosses!", -1);
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_elementor));
	if (!data)
		cub_exit("malloc failed", -1);
	trans.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	trans.rot = (t_vec2){0, 0};
	init_elementor(data);
	ntt = create_entity(trans, ELEMENTOR_NTT, \
					get_texture_elementor, tick_elementor);
	ntt->is_billboard = true;
	ntt->data = data;
	ntt->health = LMNTOR_STARTING_HEALTH;
	ntt->on_collision = on_collision_elementor;
	game()->boss = ntt;
	refresh_projectiles(data);
	return (true);
}

bool	set_key(t_vec2 pos, t_tile_type ***map)
{
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	create_entity((t_trans){{pos.x + 0.5, pos.y + 0.5}, {1.0, 0}}, \
						KEY_NTT, get_texture_key, tick_key);
	return (true);
}
