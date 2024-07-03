/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:34:27 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 12:40:40 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_goal(t_entity *self)
{
	static bool			reached = false;
	static double		reached_time = 0;
	mlx_image_t			*img;

	if (pos_dist(player()->transform.pos, self->transform.pos) > \
					GOAL_COLLISION_DISTANCE)
		return ;
	if (!reached)
	{
		logger(LOGGER_ACTION, "Goal reached!");
		reached = true;
		reached_time = mlx_get_time();
		img = mlx_texture_to_image(game()->mlx, game()->frame_win);
		mlx_image_to_window(game()->mlx, img, 0, 0);
		if (game()->screen_effect)
			mlx_delete_image(game()->mlx, game()->screen_effect); // TODO: norm
		game()->screen_effect = img;
		game()->screen_effect_end = mlx_get_time() + 2.5;
		game()->game_over = true;
		return ;
	}
	if (mlx_get_time() - reached_time > 2)
	{
		logger(LOGGER_STEP, "Closing game. Thanks for playing!");
		gc_exit(0);
	}
}

mlx_texture_t	*get_texture_goal(t_entity *self)
{
	(void)self;
	return (game()->textures.goal);
}
