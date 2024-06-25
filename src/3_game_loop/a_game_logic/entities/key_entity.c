/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:53:33 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 16:10:27 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_key(t_entity *self)
{
	if (pos_distance(player()->transform.pos, self->transform.pos) > KEY_COLLISION_DISTANCE)
		return ;
	logger(LOGGER_INFO, "Key collected!");
	player()->inv.keys++;
	delete_entity(self);
}
