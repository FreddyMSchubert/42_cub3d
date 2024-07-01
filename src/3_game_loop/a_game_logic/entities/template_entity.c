/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 17:11:44 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// called every frame
// this (or on collision) should handle death if applicable,
// check whether self->health < 0
void	tick_template(t_entity *self)
{
	(void)self;
}

// called when two entities have are closer together
// than DEFAULT_COLLISION_DISTANCE
// note that a player is not considered an entity.
// player collisions should be handled in tick
void	on_collision_template(t_entity *self, t_entity *other)
{
	(void)self;
	(void)other;
}

// also called every frame, by the renderer
mlx_texture_t	*get_texture_template(t_entity *self)
{
	(void)self;
	return (NULL);
}
