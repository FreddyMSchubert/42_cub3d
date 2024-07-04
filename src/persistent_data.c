/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:03:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/04 22:01:35 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_persistent_data	*game(void)
{
	static t_persistent_data	game;

	return (&game);
}

t_list	**gc(void)
{
	static t_list	*gc;

	if (!gc)
		gc = gc_create();
	return (&gc);
}

t_player	*player(void)
{
	static t_player	player;

	return (&player);
}


void	timing(int mode, int type)
{
	static double	start[10];
	static double	timings[10];
	int				i;

	if (mode == TIMING_MODE_START)
		start[type] = mlx_get_time();
	else if (mode == TIMING_MODE_STOP)
		timings[type] += mlx_get_time() - start[type];
	else if (mode == TIMING_MODE_CLEAR)
	{
		i = -1;
		while (++i < 10)
			timings[i] = 0;
	}
	else if (mode == TIMING_MODE_PRINT && LOG_TIMING)
		log_timing(timings);
}
