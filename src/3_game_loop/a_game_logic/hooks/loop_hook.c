/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/06/14 12:07:49 by fschuber         ###   ########.fr       */
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
		render_game_scene();
		handle_mouse_mv();
		game()->prev_time = curr_time;
	}
}
