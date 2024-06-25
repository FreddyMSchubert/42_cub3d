/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:53:33 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 19:31:10 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_key(t_entity *self)
{
	int	opening_player;

	opening_player = -1;
	if (pos_distance(player(0)->transform.pos, self->transform.pos) < KEY_COLLISION_DISTANCE)
		opening_player = 0;
	if (game()->player_count > 1 && pos_distance(player(1)->transform.pos, self->transform.pos) < KEY_COLLISION_DISTANCE)
		opening_player = 1;
	if (opening_player == -1)
		return ;
	logger(LOGGER_INFO, "Key collected!");
	player(opening_player)->inv.keys++;
	delete_entity(self);
}
