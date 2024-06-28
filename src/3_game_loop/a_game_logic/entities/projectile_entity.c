/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_entity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:56:45 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/27 22:10:47 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	shooooot(t_transform t, int type)
{
	t_entity		*projectile;
	mlx_texture_t	*texture;

	logger(LOGGER_INFO, "Shooting projectile!");
	if (type == ORB_TYPE_FIRE)
		texture = mlx_load_png("./assets/entities/fire_orb.png");
	else if (type == ORB_TYPE_AIR)
		texture = mlx_load_png("./assets/entities/air_orb.png");
	else if (type == ORB_TYPE_WATER)
		texture = mlx_load_png("./assets/entities/water_orb.png");
	else if (type == ORB_TYPE_EARTH)
		texture = mlx_load_png("./assets/entities/earth_orb.png");
	else
		texture = mlx_load_png("./assets/entities/fire_orb.png");
	if (!texture)
		logger(LOGGER_ERROR, "Failed to load projectile texture!\n");
	projectile = create_entity(t, type, texture, true, tick_projectile);
	(void)projectile;
}

void	tick_projectile(t_entity *self)
{
	t_orb	*orb;
	t_vec2	new_pos;

	orb = (t_orb *)self->data;
	self->transform.rot = scale_vector(self->transform.rot, 1);
	new_pos.x = self->transform.pos.x + self->transform.rot.x * PROJECTILE_SPEED;
	new_pos.y = self->transform.pos.y + self->transform.rot.y * PROJECTILE_SPEED;
	if (!is_position_valid(new_pos.x, new_pos.y))
	{
		delete_entity(self);
		return ;
	}
	self->transform.pos = new_pos;
	game()->dirty = true;
	if (MARK_DIRTY_LOGGING)
		logger(LOGGER_INFO, "Projectile moved, set dirty to true!\n");
	(void)orb;
}
