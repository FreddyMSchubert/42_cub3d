/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:42:00 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/27 18:13:51 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_orb(t_entity *self)
{
	t_orb	*orb;

	if (pos_distance(player()->transform.pos, self->transform.pos) > GOAL_COLLISION_DISTANCE)
		return ;
	orb = (t_orb *)self->data;
	if (orb->type == TYPE_EARTH)
	{
		player()->inv.earth_orbs += AMMO_AMOUNT_PER_ORB;
		logger(LOGGER_INFO, "Picked up some earth orbs!");
	}
	else if (orb->type == TYPE_FIRE)
	{
		player()->inv.fire_orbs += AMMO_AMOUNT_PER_ORB;
		logger(LOGGER_INFO, "Picked up some fire orbs!");
	}
	else if (orb->type == TYPE_WATER)
	{
		player()->inv.water_orbs += AMMO_AMOUNT_PER_ORB;
		logger(LOGGER_INFO, "Picked up some water orbs!");
	}
	else if (orb->type == TYPE_AIR)
	{
		player()->inv.air_orbs += AMMO_AMOUNT_PER_ORB;
		logger(LOGGER_INFO, "Picked up some air orbs!");
	}
	delete_entity(self);
}
