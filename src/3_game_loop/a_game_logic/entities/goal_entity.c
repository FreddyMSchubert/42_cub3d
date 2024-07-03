/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:34:27 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 10:17:39 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_goal(t_entity *self)
{
	static bool			reached = false;
	static double		reached_time = 0;
	static mlx_image_t	*img = NULL;

	if (pos_dist(player()->transform.pos, self->transform.pos) > \
					GOAL_COLLISION_DISTANCE)
		return ;
	if (!reached)
	{
		logger_v(LOGGER_ACTION, "Goal reached!");
		reached = true;
		reached_time = mlx_get_time();
		img = mlx_put_string(game()->mlx, "Goal reached!",
				game()->mlx->width / 2 - 60, game()->mlx->height / 2);
		game()->game_over = true;
		return ;
	}
	if (mlx_get_time() - reached_time > 2)
	{
		if (img)
			mlx_delete_image(game()->mlx, img);
		logger_v(LOGGER_STEP, "Closing game. Thanks for playing!");
		gc_exit(0);
	}
}

mlx_texture_t	*get_texture_goal(t_entity *self)
{
	(void)self;
	return (game()->textures.goal);
}
