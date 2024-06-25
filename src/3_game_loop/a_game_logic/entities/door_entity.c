/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:57:29 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 17:00:16 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_door(t_entity *self)
{
	if (pos_distance(player()->transform.pos, self->transform.pos) > DOOR_OPEN_DISTANCE || player()->inv.keys < 1)
		return ;
	logger(LOGGER_INFO, "Door unlocked!");
	player()->inv.keys--;
	((t_door *)self->data)->locked = false;
}
