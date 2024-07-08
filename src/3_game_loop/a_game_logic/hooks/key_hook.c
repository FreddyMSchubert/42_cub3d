/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/07/08 11:18:47 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static inline void	inventory_press(mlx_key_data_t keydata)
{
	if (keydata.key >= MLX_KEY_1 && keydata.key <= MLX_KEY_9 \
					&& keydata.action == MLX_PRESS)
	{
		if ((unsigned int)(player()->inv.num_available_items) > \
					keydata.key - MLX_KEY_1)
			player()->inv.current_index = keydata.key - MLX_KEY_1;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		cub_exit("ESCAPE received, exiting...", 0);
	else if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		game()->mouse_free = !game()->mouse_free;
		update_mouse_visibility();
	}
	else if (keydata.key == MLX_KEY_PERIOD)
		save_game();
	else if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		player_shoot();
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		setup_player();
	if (mlx_is_key_down(game()->mlx, MLX_KEY_C) && \
			mlx_is_key_down(game()->mlx, MLX_KEY_LEFT_CONTROL))
		cub_exit("Control + C received, exiting...", 214);
	inventory_press(keydata);
	(void) param;
}
