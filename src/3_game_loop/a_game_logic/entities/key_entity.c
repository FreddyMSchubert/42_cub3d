/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:53:33 by freddy            #+#    #+#             */
/*   Updated: 2024/07/02 13:15:42 by fschuber         ###   ########.fr       */
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
	if (player()->inv.text_amount_key)
	{
		mlx_delete_image(game()->mlx, player()->inv.text_amount_key);
		player()->inv.text_amount_key = NULL;
	}
	self->to_be_deleted = true;
}

mlx_texture_t	*get_texture_key(t_entity *self)
{
	(void)self;
	return (game()->textures.key);
}
