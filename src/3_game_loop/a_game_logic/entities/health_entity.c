/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:11:23 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 12:13:30 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_health(t_entity *self)
{
	if (pos_dist(player()->transform.pos, self->transform.pos) > HEALTH_COLLISION_DISTANCE)
		return ;
	logger(LOGGER_ACTION, "Health power up picked up!");
	player()->health += HEALTH_PICKUP_AMOUNT;
	self->to_be_deleted = true;
}

mlx_texture_t	*get_texture_health(t_entity *self)
{
	(void)self;
	return (game()->textures.health);
}
