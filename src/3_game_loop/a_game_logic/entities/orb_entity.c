/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:42:00 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/03 13:21:38 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	gain_ammo(t_entity *self, t_orb *orb)
{
	int	ammo_amount;

	ammo_amount = random_int(MIN_AMMO_AMOUNT_PER_ORB, MAX_AMMO_AMOUNT_PER_ORB);
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

static inline void	delete_old_orb_amont_text(t_orb *orb)
{
	if (orb->element == TYPE_EARTH)
	{
		mlx_delete_image(game()->mlx, player()->inv.text_amount_earth);
		player()->inv.text_amount_earth = NULL;
	}
	else if (orb->element == TYPE_FIRE)
	{
		mlx_delete_image(game()->mlx, player()->inv.text_amount_fire);
		player()->inv.text_amount_fire = NULL;
	}
	else if (orb->element == TYPE_WATER)
	{
		mlx_delete_image(game()->mlx, player()->inv.text_amount_water);
		player()->inv.text_amount_water = NULL;
	}
	else if (orb->element == TYPE_AIR)
	{
		mlx_delete_image(game()->mlx, player()->inv.text_amount_air);
		player()->inv.text_amount_air = NULL;
	}
}

void	tick_orb(t_entity *self)
{
	t_orb	*orb;

	orb = (t_orb *)self->data;
	if (pos_dist(player()->transform.pos, self->transform.pos) > \
						GOAL_COLLISION_DISTANCE)
		return ;
	gain_ammo(self, orb);
	delete_old_orb_amont_text(orb);
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
