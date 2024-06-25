/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:34:27 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 19:28:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_goal(t_entity *self)
{
	if (pos_distance(player(0)->transform.pos, self->transform.pos) > GOAL_COLLISION_DISTANCE &&
			pos_distance(player(1)->transform.pos, self->transform.pos) > GOAL_COLLISION_DISTANCE)
		return ;
	logger(LOGGER_INFO, "Goal reached!");
	cub_exit("Thanks for playing!", 0);
}
