/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elementor_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:37:35 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/06 09:12:33 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	on_collision_elementor(t_entity *self, t_entity *other)
{
	t_elementor		*elem;
	t_projectile	*projectile;
	int				health_decrease_amount;

	elem = (t_elementor *)self->data;
	if (other->type != PROJECTILE_NTT)
		return ;
	projectile = (t_projectile *)other->data;
	if (elem->stage == 0 && projectile->element == elem->element1)
		return ;
	if (elem->stage == 1 && (projectile->element == elem->element1 || \
			projectile->element == elem->element2))
		return ;
	if (elem->stage == 2 && (projectile->element == elem->element1 || \
			projectile->element == elem->element2 || \
			projectile->element == elem->element3))
		return ;
	health_decrease_amount = 0;
	if (a_beats_b(projectile->element, elem->element1))
		health_decrease_amount += LMNTOR_MAJOR_HIT_DECREASE;
	else if (a_beats_b(projectile->element, elem->element2) && elem->stage > 0)
		health_decrease_amount += LMNTOR_MAJOR_HIT_DECREASE;
	else if (a_beats_b(projectile->element, elem->element3) && elem->stage > 1)
		health_decrease_amount += LMNTOR_MAJOR_HIT_DECREASE;
	else
		health_decrease_amount += MINOR_PROJECTILE_HIT_DECREASE;
	self->health -= health_decrease_amount;
	elem->hurt_state = LMNTOR_HURT_STATE_FRAME_DURATION;
	if (self->health > 0)
		logger_v(LOGGER_ACTION, "Elementor was hit by projectile!");
	else if (elem->death_animation < 0)
	{
		logger_v(LOGGER_ACTION, "Elementor was killed by projectile!");
		elem->death_animation = 0;
	}
	other->to_be_deleted = true;
	if (elem->stage == 0)
	{
		if (random_val() > LMNTOR_RANDOM_ELEM_CHOICE_CHANCE)
			elem->element1 = projectile->element;
		else
			elem->element1 = random_int(0, 3);
		elem->frames_since_element_switch = 0;
	}
	else
		refresh_projectiles(elem);
}
