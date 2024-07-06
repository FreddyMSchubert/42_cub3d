/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elementor_tick.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:37:24 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/06 12:30:28 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	move(t_entity *self, t_elementor *elementor)
{
	t_vec2	new_pos;

	if (elementor->mvmnt == ELEMENTOR_MVMNT_STAND && \
				random_val() < LMNTOR_MVMNT_WALK_START_CHANCE)
		elementor->mvmnt = ELEMENTOR_MVMNT_WALK;
	else if (elementor->mvmnt == ELEMENTOR_MVMNT_WALK && \
				random_val() < LMNTOR_MVMNT_WALK_STOP_CHANCE)
		elementor->mvmnt = ELEMENTOR_MVMNT_STAND;
	if (elementor->mvmnt == ELEMENTOR_MVMNT_STAND)
		return ;
	self->transform.rot = scale_vector(self->transform.rot, LMNTOR_MVMNT_SPEED);
	new_pos.x = self->transform.pos.x + self->transform.rot.x;
	new_pos.y = self->transform.pos.y + self->transform.rot.y;
	if (is_position_valid(new_pos.x, new_pos.y))
		self->transform.pos = new_pos;
	else
		elementor->mvmnt = ELEMENTOR_MVMNT_STAND;
	if (random_val() > LMNTOR_MVMNT_ROT_CHANGE_CHANCE)
		return ;
	self->transform.rot = deg_to_dir_vec(random_int(0, 360));
	if (pos_dist(self->transform.pos, self->spawn_transform.pos) > LMNTOR_MAX_DISTANCE_FROM_SPAWN)
	{
		self->transform.rot.x = self->spawn_transform.pos.x - self->transform.pos.x;
		self->transform.rot.y = self->spawn_transform.pos.y - self->transform.pos.y;
	}
}

static inline void	update_stage(t_entity *self, t_elementor *elementor)
{
	int		previous;

	previous = elementor->stage;
	if (self->health < 0)
		elementor->stage = 3;
	else if (self->health < (LMNTOR_STARTING_HEALTH / 3))
		elementor->stage = 2;
	else if (self->health < 2 * (LMNTOR_STARTING_HEALTH / 3))
		elementor->stage = 1;
	else
		elementor->stage = 0;
	if (elementor->stage == 3 && elementor->death_animation == LMNTOR_DEATH_ANIM_TICKS / 2)
		elementor_logger("Oh no! What's going on? The elements - It's too much - power - HELP!");
	if (previous == elementor->stage)
		return ;
	create_entity(self->transform, HEALTH_NTT, get_texture_health, tick_health);
	if (elementor->stage == 1)
		elementor_logger("You won't defeat me! I can harness more elements than\
 you! Now, you won't be able to damage me with half of your orbs!");
	else if (elementor->stage == 2)
		elementor_logger("Aaaargh! Stop doing that! It is futile anyways. With \
the power of another element, you can't even dream of stopping me!");
	else if (elementor->stage == 3)
		elementor_logger("You good-for-nothing human! You think you can defeat \
me? I am the master of all elements! I will crush you!");
}

void	tick_elementor(t_entity *self)
{
	t_elementor	*elementor;

	elementor = (t_elementor *)self->data;
	elementor->animation_frame++;
	elementor->frames_since_element_switch++;
	elementor->death_animation += elementor->death_animation >= 0;
	elementor->hurt_state -= elementor->hurt_state > 0;
	update_stage(self, elementor);
	move(self, elementor);
	elementor_attack(self, elementor);
	if (elementor->frames_since_element_switch > LMNTOR_MAX_SAME_ELEMENT_FRAMES)
	{
		refresh_projectiles(elementor);
		elementor->frames_since_element_switch = 0;
	}
	if (elementor->death_animation > LMNTOR_DEATH_ANIM_TICKS)
	{
		self->to_be_deleted = true;
		game()->boss = NULL;
		create_entity(self->transform, KEY_NTT, get_texture_key, tick_key);
		elementor_logger("Nooooooooooooooooooooooooooooooooooooooooooo!");
		nuke(self->transform.pos);
	}
}
