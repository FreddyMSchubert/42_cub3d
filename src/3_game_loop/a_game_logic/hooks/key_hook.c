/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 14:07:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

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
	// else if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	// 	hud_toogle_worldmap(true);
	(void) param;
}
