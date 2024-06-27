/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_entity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:45 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/27 20:37:13 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	shooooot(t_transform t, int type)
{
	mlx_texture_t	*texture;
	t_entity		*ntt;
	t_projectile	*projectile;

	logger(LOGGER_ACTION, "Shot projectile!");
	texture = NULL;
	if (type == TYPE_FIRE)
		texture = game()->textures.fire_orb;
	else if (type == TYPE_AIR)
		texture = game()->textures.air_orb;
	else if (type == TYPE_WATER)
		texture = game()->textures.water_orb;
	else if (type == TYPE_EARTH)
		texture = game()->textures.earth_orb;
	if (!texture)
		logger(LOGGER_ERROR, "Failed to load projectile texture!\n");
	ntt = create_entity(t, PROJECTILE_E, texture, true, tick_projectile);
	projectile = gc_malloc(sizeof(t_orb));
	projectile->type = type;
	ntt->data = projectile;
}

void	tick_projectile(t_entity *self)
{
	t_vec2	new_pos;

	self->transform.rot = scale_vector(self->transform.rot, 1);
	new_pos.x = self->transform.pos.x + self->transform.rot.x * PROJECTILE_SPEED;
	new_pos.y = self->transform.pos.y + self->transform.rot.y * PROJECTILE_SPEED;
	if (!is_position_valid(new_pos.x, new_pos.y))
	{
		delete_entity(self);
		game()->dirty = true;
		return ;
	}
	self->transform.pos = new_pos;
	game()->dirty = true;
	if (MARK_DIRTY_LOGGING)
		logger(LOGGER_DIRTY, "Projectile moved, set dirty to true!\n");
}
