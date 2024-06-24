/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 14:24:02 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static int	get_frame(double time)
{
	return ((int)((time - floor(time)) * FPS));
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
	if (curr_frame > prev_frame + 1)
		logger(LOGGER_WARNING, "skipped frame");
	if ((int)curr_time != (int)prev_time || curr_frame != prev_frame)
	{
		game()->dirty = false;
		handle_mouse_mv();
		handle_player_move();
		if (game()->dirty == true)
		{
			write(1, "dirty\n", 6);
			if (MARK_DIRTY_LOGGING)
				printf("is dirty, rendering new!\n");
			render_game_scene();
			hud_draw();
			game()->dirty = false;
		}
		game()->prev_time = curr_time;
	}
}
