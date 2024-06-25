/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 19:29:56 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_door(t_entity *self)
{
	t_door	*door;
	int		opening_player;

	door = (t_door *)self->data;
	if (door->state == DOOR_STATE_OPEN)
		return ;
	else if (door->state == DOOR_STATE_CLOSED)
	{
		opening_player = -1;
		if (pos_distance(player(0)->transform.pos, self->transform.pos) < DOOR_OPEN_DISTANCE && player(0)->inv.keys > 0)
			opening_player = 0;
		else if (game()->player_count > 1 && pos_distance(player(1)->transform.pos, self->transform.pos) < DOOR_OPEN_DISTANCE && player(1)->inv.keys > 0)
			opening_player = 1;
		if (opening_player == -1)
			return ;
		logger(LOGGER_INFO, "Door unlocked!");
		player(opening_player)->inv.keys--;
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
		player(0)->dirty = true;
		player(1)->dirty = true;
		if (MARK_DIRTY_LOGGING)
			logger(LOGGER_INFO, "Door opening, set dirty to true!\n");
		if (door->door_open_progress <= 0)
		{
			self->transform.pos = door->open_pos;
			door->state = DOOR_STATE_OPEN;
		}
	}
}
