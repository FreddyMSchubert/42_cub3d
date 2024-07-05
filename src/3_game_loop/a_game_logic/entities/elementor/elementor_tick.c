/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elementor_tick.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:37:24 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/05 14:33:14 by freddy           ###   ########.fr       */
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
}

void	tick_elementor(t_entity *self)
{
	t_elementor	*elementor;

	elementor = (t_elementor *)self->data;
	move(self, elementor);
	elementor->animation_frame++;
}
