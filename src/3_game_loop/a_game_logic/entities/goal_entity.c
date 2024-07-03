/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:34:27 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 14:26:25 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	display_win_screen(void)
{
	mlx_image_t	*img;

	if (game()->screen_effect)
		mlx_delete_image(game()->mlx, game()->screen_effect);
	img = mlx_new_image(game()->mlx, game()->mlx->width, game()->mlx->height);
	mlx_image_to_window(game()->mlx, img, 0, 0);
	game()->screen_effect = img;
	screen_texture_draw(game()->frame_win, (t_scale){0, 0},
		(t_scale){game()->mlx->width, game()->mlx->height});
	game()->screen_effect_end = mlx_get_time() + 2.5;
	game()->game_over = true;
}

void	tick_goal(t_entity *self)
{
	static bool			reached = false;
	static double		reached_time = 0;

	if (pos_dist(player()->transform.pos, self->transform.pos) > \
					GOAL_COLLISION_DISTANCE)
		return ;
	if (!reached)
	{
		logger_v(LOGGER_ACTION, "Goal reached!");
		reached = true;
		reached_time = mlx_get_time();
		display_win_screen();
		game()->game_over = true;
		return ;
	}
	if (mlx_get_time() - reached_time > 2)
	{
		save_game();
		logger_v(LOGGER_STEP, "Closing game. Thanks for playing!");
		gc_exit(0);
	}
}

mlx_texture_t	*get_texture_goal(t_entity *self)
{
	(void)self;
	return (game()->textures.goal);
}
