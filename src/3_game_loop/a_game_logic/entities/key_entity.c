/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:53:33 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 17:12:16 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_key(t_entity *self)
{
	if (pos_dist(player()->transform.pos, self->transform.pos) > \
					KEY_COLLISION_DISTANCE)
		return ;
	logger(LOGGER_ACTION, "Key collected!");
	player()->inv.keys++;
	self->to_be_deleted = true;
}

mlx_texture_t	*get_texture_key(t_entity *self)
{
	(void)self;
	return (game()->textures.key);
}
