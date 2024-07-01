/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ORB_NTTntity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:42:00 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/27 20:56:46 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_orb(t_entity *self)
{
	t_orb	*orb;
	int		ammo_amount;

	if (pos_dist(player()->transform.pos, self->transform.pos) > GOAL_COLLISION_DISTANCE)
		return ;
	ammo_amount = random_int(MIN_AMMO_AMOUNT_PER_ORB, MAX_AMMO_AMOUNT_PER_ORB);
	orb = (t_orb *)self->data;
	if (orb->element == TYPE_EARTH)
	{
		player()->inv.earth_orbs += ammo_amount;
		logger(LOGGER_ACTION, "Picked up some earth orbs!");
	}
	else if (orb->element == TYPE_FIRE)
	{
		player()->inv.fire_orbs += ammo_amount;
		logger(LOGGER_ACTION, "Picked up some fire orbs!");
	}
	else if (orb->element == TYPE_WATER)
	{
		player()->inv.water_orbs += ammo_amount;
		logger(LOGGER_ACTION, "Picked up some water orbs!");
	}
	else if (orb->element == TYPE_AIR)
	{
		player()->inv.air_orbs += ammo_amount;
		logger(LOGGER_ACTION, "Picked up some air orbs!");
	}
	self->to_be_deleted = true;
}

mlx_texture_t	*get_texture_orb(t_entity *self)
{
	if (((t_blight *)self->data)->element == TYPE_FIRE)
		return (game()->textures.fire_orb);
	else if (((t_blight *)self->data)->element == TYPE_AIR)
		return (game()->textures.air_orb);
	else if (((t_blight *)self->data)->element == TYPE_WATER)
		return (game()->textures.water_orb);
	else if (((t_blight *)self->data)->element == TYPE_EARTH)
		return (game()->textures.earth_orb);
	return (NULL);
}
