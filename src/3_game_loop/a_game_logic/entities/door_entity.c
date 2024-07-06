/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:11:55 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	unlock_door_if_possible(t_entity *self, t_door *door)
{
	if (pos_dist(player()->trans.pos, self->trans.pos)
		> DOOR_OPEN_DISTANCE || player()->inv.keys < 1
		|| player()->inv.current_index != 0)
		return ;
	logger_v(LOGGER_ACTION, "Door unlocked!");
	player()->inv.keys--;
	if (player()->inv.text_amount_key)
	{
		mlx_delete_image(game()->mlx, player()->inv.text_amount_key);
		player()->inv.text_amount_key = NULL;
	}
	door->state = DOOR_STATE_OPENING;
	door->close_pos = self->trans.pos;
	door->open_pos = self->trans.pos;
	if (door->direction == DOOR_DIR_HORIZONTAL)
		door->open_pos.x += 1;
	else
		door->open_pos.y += 1;
	door->door_open_progress = 1.0;
}

void	tick_door(t_entity *self)
{
	t_door	*door;

	door = (t_door *)self->data;
	if (door->state == DOOR_STATE_OPEN)
	{
		self->to_be_deleted = true;
		return ;
	}
	else if (door->state == DOOR_STATE_CLOSED)
		unlock_door_if_possible(self, door);
	else if (door->state == DOOR_STATE_OPENING)
	{
		door->door_open_progress -= DOOR_OPEN_SPEED;
		self->trans.pos.x += ((door->open_pos.x - door->close_pos.x) * \
								DOOR_OPEN_SPEED);
		self->trans.pos.y += ((door->open_pos.y - door->close_pos.y) * \
								DOOR_OPEN_SPEED);
		if (door->door_open_progress <= 0)
		{
			self->trans.pos = door->open_pos;
			door->state = DOOR_STATE_OPEN;
		}
	}
}

mlx_texture_t	*get_texture_door(t_entity *self)
{
	(void)self;
	return (game()->textures.door);
}
