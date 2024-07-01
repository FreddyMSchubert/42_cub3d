/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:27:28 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 17:30:08 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline bool	check_door_collisions(float x, float y, t_entity *ntt)
{
	t_door	*door;
	float	pos_on_space;

	door = (t_door *)ntt->data;
	if (door->state != DOOR_STATE_OPEN)
	{
		if (door->direction == DOOR_DIR_HORIZONTAL)
		{
			pos_on_space = fmod(y, 1.0f);
			if (floor(x) == floor(ntt->transform.pos.x) && \
								floor(y) == floor(ntt->transform.pos.y) && \
					pos_on_space > CLOSED_DOOR_ALLOWED_WALK_DISTANCE && \
						pos_on_space < 1 - CLOSED_DOOR_ALLOWED_WALK_DISTANCE)
				return (false);
		}
		else
		{
			pos_on_space = fmod(x, 1.0f);
			if (floor(y) == floor(ntt->transform.pos.y) && \
						floor(x) == floor(ntt->transform.pos.x) && \
					pos_on_space > CLOSED_DOOR_ALLOWED_WALK_DISTANCE && \
						pos_on_space < 1 - CLOSED_DOOR_ALLOWED_WALK_DISTANCE)
				return (false);
		}
	}
}

bool	is_position_valid(float x, float y)
{
	t_list		*ntt_list;
	t_entity	*ntt;
	t_door		*door;

	if (x < 0 || x >= game()->input_data->map_width || y < 0 || \
		y >= game()->input_data->map_height || \
		*game()->input_data->map[(int)y][(int)x] != FLOOR)
		return (false);
	ntt_list = game()->entities;
	while (ntt_list)
	{
		ntt = (t_entity *)ntt_list->content;
		if (ntt->type == DOOR_NTT)
			if (!check_door_collisions(x, y, ntt))
				return (false);
		ntt_list = ntt_list->next;
	}
	return (true);
}
