/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 13:58:34 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	show_death_screen(void)
{
	static double	start_time = -1.0;
	mlx_image_t		*frame_dead;

	if (start_time == -1.0)
	{
		printf("showing death screen\n");
		if (game()->screen_effect)
			mlx_delete_image(game()->mlx, game()->screen_effect);
		frame_dead = mlx_new_image(game()->mlx, game()->mlx->width,
				game()->mlx->height);
		if (!frame_dead)
			cub_exit("Failed to create death screen", -1);
		game()->screen_effect = frame_dead;
		mlx_image_to_window(game()->mlx, frame_dead, 0, 0);
		screen_texture_draw(game()->frame_dead, (t_scale){0, 0},
			(t_scale){game()->mlx->width, game()->mlx->height});
		start_time = mlx_get_time();
	}
	if (mlx_get_time() - start_time < 2.0)
		return ;
	cub_exit("Quitting program. Playing as a corpse is dull.", 0);
}

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
	if (game()->screen_effect && game()->screen_effect_end < curr_time)
	{
		mlx_delete_image(game()->mlx, game()->screen_effect);
		game()->screen_effect = NULL;
	}
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
		logger_v(LOGGER_WARNING, "skipped frame");
	if (((int)curr_time != (int)prev_time || curr_frame != prev_frame)
		&& !game()->game_over)
		game_tick(curr_time);
	else if (((int)curr_time != (int)prev_time || curr_frame != prev_frame)
		&& game()->game_over && player()->health > 0)
		tick_entities();
	else if (game()->game_over && player()->health <= 0)
		show_death_screen();
}
