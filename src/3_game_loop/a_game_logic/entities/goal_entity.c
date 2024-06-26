/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:34:27 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 17:10:11 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_goal(t_entity *self)
{
	if (pos_dist(player()->transform.pos, self->transform.pos) > \
					GOAL_COLLISION_DISTANCE)
		return ;
	logger(LOGGER_ACTION, "Goal reached!");
	logger(LOGGER_STEP, "Closing game. Thanks for playing!");
	gc_exit(0);
}

mlx_texture_t	*get_texture_goal(t_entity *self)
{
	(void)self;
	return (game()->textures.goal);
}
