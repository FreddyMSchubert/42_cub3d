/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:57:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 12:38:15 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	rotate_self(t_entity *self)
{
	double	prev_angle;
	double	new_angle;
	t_vec2	new_dir;

	if (pos_distance(self->transform.pos, self->spawn_transform.pos) > BLIGHT_MAX_SPAWN_DISTANCE)
	{
		new_dir.x = self->spawn_transform.pos.x - self->transform.pos.x;
		new_dir.y = self->spawn_transform.pos.y - self->transform.pos.y;
		new_angle = dir_vec_to_deg(new_dir);
		new_angle += random_val() * BLIGHT_SPAWN_RETURNING_DEG_VARIATION - (BLIGHT_SPAWN_RETURNING_DEG_VARIATION / 2);
		self->transform.rot = deg_to_dir_vec(new_angle);
		return ;
	}

	prev_angle = dir_vec_to_deg(self->transform.rot);
	self->transform.rot.x = (random_val() * 2) - 1;
	self->transform.rot.y = (random_val() * 2) - 1;
	new_angle = dir_vec_to_deg(self->transform.rot);
	if (fabs(prev_angle - new_angle) < BLIGHT_MINIUM_ROTATION_DEG)
		rotate_self(self);
}

void	move_self(t_entity *self)
{
	t_vec2	new_pos;
	t_vec2	oldpos;

	oldpos = self->transform.pos;
	self->transform.rot = scale_vector(self->transform.rot, 1);
	if (random_val() < BLIGHT_MOVEMENT_ROTATION_SWITCH_CHANCE)
		rotate_self(self);
	new_pos.x = self->transform.pos.x + self->transform.rot.x * BLIGHT_SPEED;
	new_pos.y = self->transform.pos.y + self->transform.rot.y * BLIGHT_SPEED;
	if (is_position_valid(new_pos.x, new_pos.y))
	{
		self->transform.pos.x = new_pos.x;
		self->transform.pos.y = new_pos.y;
	}
	else
		rotate_self(self);
	if (oldpos.x != self->transform.pos.x || oldpos.y != self->transform.pos.y)
	{
		game()->dirty = true;
		if (MARK_DIRTY_LOGGING)
			logger(LOGGER_INFO, "Blight moved, marking dirty!");
	}
}

void	tick_blight(t_entity *self)
{
	t_blight	*blight;

	blight = (t_blight *)self->data;
	if (blight->state == BLIGHT_STATE_WALKING)
	{
		move_self(self);
		if (random_val() < BLIGHT_STANDING_START_CHANCE)
		{
			blight->state = BLIGHT_STATE_STANDING;
			game()->dirty = true;
			if (MARK_DIRTY_LOGGING)
				logger(LOGGER_INFO, "Blight stopped, marking dirty!");
		}
	}
	else if (blight->state == BLIGHT_STATE_STANDING)
	{
		if (random_val() < BLIGHT_WALKING_START_CHANCE)
		{
			blight->state = BLIGHT_STATE_WALKING;
		}
	}
}
