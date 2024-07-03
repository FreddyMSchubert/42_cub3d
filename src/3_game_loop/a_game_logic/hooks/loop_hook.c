/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 09:49:06 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static int	get_frame(double time)
{
	return ((int)((time - floor(time)) * FPS));
}

static inline void	game_tick(double curr_time)
{
	handle_mouse_mv();
	handle_player_move();
	tick_entities();
	collide_entities();
	render();
	game()->prev_time = curr_time;
	check_dead_player();
}

void	loop_hook(void *param)
{
	double	curr_time;
	double	prev_time;
	int		curr_frame;
	int		prev_frame;

	(void) param;
	curr_time = mlx_get_time();
	prev_time = game()->prev_time;
	curr_frame = get_frame(curr_time);
	prev_frame = get_frame(prev_time);
	if (curr_frame > prev_frame + 1 && DEBUG)
		logger(LOGGER_WARNING, "skipped frame");
	if (((int)curr_time != (int)prev_time || curr_frame != prev_frame)
		&& !game()->game_over)
	{
		game_tick(curr_time);
	}
	else if (((int)curr_time != (int)prev_time || curr_frame != prev_frame)
		&& game()->game_over)
	{
		tick_entities();
	}
}
