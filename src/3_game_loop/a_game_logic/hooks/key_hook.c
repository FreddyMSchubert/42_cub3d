/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 12:32:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"
#include <stdio.h>

static inline void	inventory_press(mlx_key_data_t keydata)
{
	if (keydata.key >= MLX_KEY_1 && keydata.key <= MLX_KEY_9 && keydata.action == MLX_PRESS)
	{
		if ((unsigned int)(player()->inv.num_available_items) > keydata.key - MLX_KEY_1)
		{
			player()->inv.current_index = keydata.key - MLX_KEY_1;
			game()->dirty = true;
		}
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game()->mlx);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		turn (-TURN_SPEED_ARROWS_DEG);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		turn (TURN_SPEED_ARROWS_DEG);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		setup_player();
	inventory_press(keydata);
	game()->dirty = true;
	(void) param;
}
