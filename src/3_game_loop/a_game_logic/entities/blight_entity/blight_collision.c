/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:57:58 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:11:55 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	on_collision_blight(t_entity *self, t_entity *other)
{
	t_blight	*blight;
	int			health_decrease_amount;

	blight = (t_blight *)self->data;
	if (!(other->type == PROJECTILE_NTT) || \
					blight->element == ((t_projectile *)other->data)->element)
		return ;
	if (a_beats_b(((t_projectile *)other->data)->element, blight->element))
		health_decrease_amount = MAJOR_PROJECTILE_HIT_DESCREASE;
	else
		health_decrease_amount = MINOR_PROJECTILE_HIT_DECREASE;
	self->health -= health_decrease_amount;
	blight->hurt_state = BLIGHT_HURT_STATE_FRAME_DURATION;
	if (self->health > 0)
		logger_v(LOGGER_ACTION, "Blight hit by projectile!");
	else if (blight->state != BLIGHT_STATE_DYING)
	{
		logger_v(LOGGER_ACTION, "Blight killed by projectile!");
		blight->state = BLIGHT_STATE_DYING;
		if (blight->drops_key)
			create_entity(self->trans, KEY_NTT, get_texture_key, tick_key);
	}
	other->to_be_deleted = true;
}
