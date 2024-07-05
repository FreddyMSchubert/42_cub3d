/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:03:47 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/05 14:34:07 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_door(t_vec2 pos, t_tile_type ***map, char type)
{
	t_door			*data;
	t_entity		*ntt;
	t_transform		trans;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_door));
	if (!data)
		cub_exit("malloc failed", -1);
	if (type == 'H')
		data->direction = DOOR_DIR_HORIZONTAL;
	else
		data->direction = DOOR_DIR_VERTICAL;
	trans.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	trans.rot = (t_vec2){0, 0};
	if (data->direction == DOOR_DIR_HORIZONTAL)
		trans.rot.x = 1;
	else
		trans.rot.y = 1;
	data->state = DOOR_STATE_CLOSED;
	ntt = create_entity(trans, DOOR_NTT, get_texture_door, tick_door);
	ntt->is_billboard = false;
	ntt->data = data;
	return (true);
}

bool	set_boss(t_vec2 pos, t_tile_type ***map)
{
	t_elementor	*data;
	t_entity	*ntt;
	t_transform	trans;
	static int	count;

	if (++count > 1)
		cub_exit("Too many bosses!", -1);
	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = malloc(sizeof(t_elementor));
	if (!data)
		cub_exit("malloc failed", -1);
	trans.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	trans.rot = (t_vec2){0, 0};
	data->element1 = random_int(0, 3);
	data->element2 = random_int(0, 3);
	data->element3 = random_int(0, 3);
	data->stage = 1;
	data->mvmnt = ELEMENTOR_MVMNT_STAND;
	data->attack = ELEMENTOR_ATTACK_NONE;
	data->animation_frame = 0;
	ntt = create_entity(trans, ELEMENTOR_NTT, \
					get_texture_elementor, tick_elementor);
	ntt->is_billboard = true;
	ntt->data = data;
	game()->boss = ntt;
	return (true);
}
