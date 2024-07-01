/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:57:58 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 17:20:15 by freddy           ###   ########.fr       */
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
	if (self->health > 0)
		logger(LOGGER_ACTION, "Blight hit by projectile!");
	else
	{
		logger(LOGGER_ACTION, "Blight killed by projectile!");
		blight->state = BLIGHT_STATE_DYING;
	}
	other->to_be_deleted = true;
}
