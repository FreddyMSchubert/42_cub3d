/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:42:00 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/26 14:40:21 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_orb(t_entity *self)
{
	t_orb	*orb;

	if (pos_distance(player()->transform.pos, self->transform.pos) > GOAL_COLLISION_DISTANCE)
		return ;
	orb = (t_orb *)self->data;
	if (orb->type == ORB_TYPE_EARTH)
		player()->inv.earth_orbs++;
	else if (orb->type == ORB_TYPE_FIRE)
		player()->inv.fire_orbs++;
	else if (orb->type == ORB_TYPE_WATER)
		player()->inv.water_orbs++;
	else if (orb->type == ORB_TYPE_AIR)
		player()->inv.air_orbs++;
	logger(LOGGER_INFO, "Picked up orb!");
	delete_entity(self);
}
