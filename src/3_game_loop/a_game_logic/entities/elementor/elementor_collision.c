/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elementor_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:37:35 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/06 20:27:31 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline bool	projectile_does_damage(int element, t_elementor *elem)
{
	if (elem->stage == 0 && element == elem->element1)
		return (false);
	if (elem->stage == 1 && (element == elem->element1 || \
			element == elem->element2))
		return (false);
	if (elem->stage == 2 && (element == elem->element1 || \
			element == elem->element2 || \
			element == elem->element3))
		return (false);
	return (true);
}

static inline int	calc_damage(t_projectile *projectile, t_elementor *elem)
{
	if (a_beats_b(projectile->element, elem->element1))
		return (LMNTOR_MAJOR_HIT_DECREASE);
	if (a_beats_b(projectile->element, elem->element2) && elem->stage > 0)
		return (LMNTOR_MAJOR_HIT_DECREASE);
	if (a_beats_b(projectile->element, elem->element3) && elem->stage > 1)
		return (LMNTOR_MAJOR_HIT_DECREASE);
	return (MINOR_PROJECTILE_HIT_DECREASE);
}

void	on_collision_elementor(t_entity *self, t_entity *other)
{
	t_elementor		*elem;
	t_projectile	*projectile;

	elem = (t_elementor *)self->data;
	if (other->type != PROJECTILE_NTT)
		return ;
	projectile = (t_projectile *)other->data;
	if (!projectile_does_damage(projectile->element, elem))
		return ;
	self->health -= calc_damage(projectile, elem);
	elem->hurt_state = LMNTOR_HURT_STATE_FRAME_DURATION;
	if (self->health > 0)
		logger_v(LOGGER_ACTION, "Elementor was hit by projectile!");
	else if (elem->death_animation < 0)
	{
		logger_v(LOGGER_ACTION, "Elementor was killed by projectile!");
		elem->death_animation = 0;
	}
	other->to_be_deleted = true;
	refresh_projectiles(elem);
}
