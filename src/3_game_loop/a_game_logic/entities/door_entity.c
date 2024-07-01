/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DOOR_NTTntity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 20:57:09 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_door(t_entity *self)
{
	t_door	*door;

	door = (t_door *)self->data;
	if (door->state == DOOR_STATE_OPEN)
		return ;
	else if (door->state == DOOR_STATE_CLOSED)
	{
		if (pos_dist(player()->transform.pos, self->transform.pos) > DOOR_OPEN_DISTANCE || player()->inv.keys < 1)
			return ;
		logger(LOGGER_ACTION, "Door unlocked!");
		player()->inv.keys--;
		door->state = DOOR_STATE_OPENING;
		door->close_pos = self->transform.pos;
		door->open_pos = self->transform.pos;
		if (door->direction == DOOR_DIR_HORIZONTAL)
			door->open_pos.x += 1;
		else
			door->open_pos.y += 1;
		door->door_open_progress = 1.0;
	}
	else if (door->state == DOOR_STATE_OPENING)
	{
		door->door_open_progress -= DOOR_OPEN_SPEED;
		self->transform.pos.x += ((door->open_pos.x - door->close_pos.x) * DOOR_OPEN_SPEED);
		self->transform.pos.y += ((door->open_pos.y - door->close_pos.y) * DOOR_OPEN_SPEED);
		if (door->door_open_progress <= 0)
		{
			self->transform.pos = door->open_pos;
			door->state = DOOR_STATE_OPEN;
		}
	}
}

mlx_texture_t	*get_texture_door(t_entity *self)
{
	(void)self;
	return (game()->textures.door);
}
