/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/07/08 13:00:55 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	unlock_door_if_possible(t_entity *self, t_door *door)
{
	if (pos_dist(player()->trans.pos, door->idle_pos) > DOOR_OPEN_DISTANCE)
		return ;
	if ((player()->inv.keys < 1 || player()->inv.current_index != 0) \
					&& door->type != DOOR_TYPE_UNLOCKED)
		return ;
	logger_v(LOGGER_ACTION, "Door unlocked!");
	if (door->type == DOOR_TYPE_LOCKED)
	{
		player()->inv.keys--;
		if (player()->inv.text_amount_key)
		{
			mlx_delete_image(game()->mlx, player()->inv.text_amount_key);
			player()->inv.text_amount_key = NULL;
		}
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

static inline void	close_door_if_possible(t_entity *self, t_door *door)
{
	if (pos_dist(player()->trans.pos, door->idle_pos) < DOOR_OPEN_DISTANCE)
		return ;
	if (door->type == DOOR_TYPE_LOCKED)
		return ;
	door->state = DOOR_STATE_CLOSING;
	door->close_pos = self->trans.pos;
	door->open_pos = self->trans.pos;
	if (door->direction == DOOR_DIR_HORIZONTAL)
		door->close_pos.x -= 1;
	else
		door->close_pos.y -= 1;
	door->door_open_progress = 1.0;
}

static inline void	move_door(t_entity *self, t_door *door)
{
	float	move_amount_x;
	float	move_amount_y;
	int		direction;

	move_amount_x = (door->open_pos.x - door->close_pos.x) * DOOR_OPEN_SPEED;
	move_amount_y = (door->open_pos.y - door->close_pos.y) * DOOR_OPEN_SPEED;
	direction = 1;
	if (door->state == DOOR_STATE_CLOSING)
		direction = -1;
	door->door_open_progress -= DOOR_OPEN_SPEED;
	self->trans.pos.x += move_amount_x * direction;
	self->trans.pos.y += move_amount_y * direction;
	if (door->door_open_progress <= 0)
	{
		if (direction == -1)
			self->trans.pos = door->close_pos;
		else
			self->trans.pos = door->open_pos;
		if (direction == -1)
			door->state = DOOR_STATE_CLOSED;
		else
			door->state = DOOR_STATE_OPEN;
	}
}

void	tick_door(t_entity *self)
{
	t_door	*door;

	door = (t_door *)self->data;
	if (door->state == DOOR_STATE_OPEN)
	{
		if (door->type == DOOR_TYPE_LOCKED)
			self->to_be_deleted = true;
		else
			close_door_if_possible(self, door);
	}
	else if (door->state == DOOR_STATE_CLOSED)
		unlock_door_if_possible(self, door);
	else if (door->state == DOOR_STATE_OPENING || \
			door->state == DOOR_STATE_CLOSING)
		move_door(self, door);
}

mlx_texture_t	*get_texture_door(t_entity *self)
{
	t_door	*door;

	door = (t_door *)self->data;
	if (door->type == DOOR_TYPE_LOCKED)
		return (game()->textures.door);
	else
		return (game()->textures.door_open);
}
