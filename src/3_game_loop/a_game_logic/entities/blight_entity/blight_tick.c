/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_tick.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:57:26 by freddy            #+#    #+#             */
/*   Updated: 2024/07/10 10:26:53 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define MAX_ROTATE_SELF_DEPTH 3

static void	rotate_self(t_entity *self, int depth)
{
	double	prev_angle;
	double	new_angle;
	t_vec2	new_dir;

	if (pos_dist(self->trans.pos, self->spawn_trans.pos) > \
								BLIGHT_MAX_SPAWN_DISTANCE)
	{
		new_dir.x = self->spawn_trans.pos.x - self->trans.pos.x;
		new_dir.y = self->spawn_trans.pos.y - self->trans.pos.y;
		new_angle = dir_vec_to_deg(new_dir);
		new_angle += random_val() * BLIGHT_SPAWN_RETURNING_DEG_VARIATION - \
								(BLIGHT_SPAWN_RETURNING_DEG_VARIATION / 2);
		self->trans.rot = deg_to_dir_vec(new_angle);
		return ;
	}
	prev_angle = dir_vec_to_deg(self->trans.rot);
	self->trans.rot.x = (random_val() * 2) - 1;
	self->trans.rot.y = (random_val() * 2) - 1;
	new_angle = dir_vec_to_deg(self->trans.rot);
	if (fabs(prev_angle - new_angle) < BLIGHT_MINIUM_ROTATION_DEG && \
			depth < MAX_ROTATE_SELF_DEPTH)
		rotate_self(self, depth + 1);
}

static inline void	move_self(t_entity *self)
{
	t_vec2	new_pos;

	self->trans.rot = scale_vector(self->trans.rot, 1);
	if (random_val() < BLIGHT_MOVEMENT_ROTATION_SWITCH_CHANCE)
		rotate_self(self, 0);
	new_pos.x = self->trans.pos.x + self->trans.rot.x * BLIGHT_SPEED;
	new_pos.y = self->trans.pos.y + self->trans.rot.y * BLIGHT_SPEED;
	if (is_position_valid(new_pos.x, new_pos.y))
	{
		self->trans.pos.x = new_pos.x;
		self->trans.pos.y = new_pos.y;
	}
	else
		rotate_self(self, 0);
}

static inline void	blight_attack(t_entity *self, t_blight *blight)
{
	if (self->frames_since_state_change > BLIGHT_ATTACK_ANIMATION_FRAMES)
	{
		self->trans.rot.x = \
							player()->trans.pos.x - self->trans.pos.x;
		self->trans.rot.y = \
							player()->trans.pos.y - self->trans.pos.y;
		self->trans.rot = scale_vector(self->trans.rot, 1);
		self->trans.rot = deg_to_dir_vec(\
						dir_vec_to_deg(self->trans.rot) + (random_val() * \
						BLIGHT_SHOOTING_INACCURACY_DEG - \
						(BLIGHT_SHOOTING_INACCURACY_DEG / 2)));
		shooooot(self->trans, blight->element);
		blight->state = BLIGHT_STATE_WALKING;
		self->frames_since_state_change = 0;
	}
}

static inline void	blight_walk(t_entity *self, t_blight *blight)
{
	move_self(self);
	if (random_val() < BLIGHT_STANDING_START_CHANCE)
	{
		blight->state = BLIGHT_STATE_STANDING;
		self->frames_since_state_change = 0;
		if (random_val() < BLIGHT_ATTACKING_START_CHANCE)
			blight->state = BLIGHT_STATE_ATTACKING;
	}
}

void	tick_blight(t_entity *self)
{
	t_blight	*blight;

	if (!self)
		return ;
	self->frames_since_state_change++;
	blight = (t_blight *)self->data;
	if (blight->hurt_state > 0)
		blight->hurt_state--;
	if (blight->state == BLIGHT_STATE_WALKING)
		blight_walk(self, blight);
	else if (blight->state == BLIGHT_STATE_STANDING && \
						random_val() < BLIGHT_WALKING_START_CHANCE)
	{
		blight->state = BLIGHT_STATE_WALKING;
		self->frames_since_state_change = 0;
	}
	else if (blight->state == BLIGHT_STATE_DYING && \
			self->frames_since_state_change > BLIGHT_DEATH_ANIMATION_FRAMES)
	{
		logger_v(LOGGER_ACTION, "Blight died!");
		drop_orbs(self->trans, blight->element);
		if (blight->drops_key)
		{
			create_entity(self->trans, KEY_NTT, get_texture_key, tick_key);
			blight->drops_key = false;
		}
		self->to_be_deleted = true;
	}
	else if (blight->state == BLIGHT_STATE_ATTACKING)
		blight_attack(self, blight);
}
