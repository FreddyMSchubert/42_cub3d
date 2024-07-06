/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_entity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:45 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/06 20:11:55 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	shooooot(t_trans t, int element)
{
	t_entity		*ntt;
	t_projectile	*projectile;

	ntt = create_entity(t, PROJECTILE_NTT, get_texture_projectile, \
					tick_projectile);
	projectile = malloc(sizeof(t_orb));
	if (!projectile)
		cub_exit("malloc failed", -1);
	projectile->element = element;
	ntt->data = projectile;
}

void	tick_projectile(t_entity *self)
{
	t_vec2	new_pos;

	self->trans.rot = scale_vector(self->trans.rot, 1);
	new_pos.x = self->trans.pos.x + self->trans.rot.x * \
						PROJECTILE_SPEED;
	new_pos.y = self->trans.pos.y + self->trans.rot.y * \
						PROJECTILE_SPEED;
	if (!is_position_valid(new_pos.x, new_pos.y))
	{
		self->to_be_deleted = true;
		return ;
	}
	self->trans.pos = new_pos;
}

mlx_texture_t	*get_texture_projectile(t_entity *self)
{
	if (((t_blight *)self->data)->element == TYPE_FIRE)
		return (game()->textures.fire_orb_flying);
	else if (((t_blight *)self->data)->element == TYPE_AIR)
		return (game()->textures.air_orb_flying);
	else if (((t_blight *)self->data)->element == TYPE_WATER)
		return (game()->textures.water_orb_flying);
	else if (((t_blight *)self->data)->element == TYPE_EARTH)
		return (game()->textures.earth_orb_flying);
	return (NULL);
}
