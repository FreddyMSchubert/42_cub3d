/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 15:31:58 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// called every frame
void	tick_template(t_entity *self)
{
	(void)self;
}

// called when two entities have are closer together than DEFAULT_COLLISION_DISTANCE
// note that a player is not considered an entity. player collisions should be handled in tick
void	on_collision_template(t_entity *self, t_entity *other)
{
	(void)self;
	(void)other;
}
