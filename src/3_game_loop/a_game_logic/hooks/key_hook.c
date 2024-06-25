/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 19:19:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static inline void	handle_player(mlx_key_data_t keydata, int id)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player(id)->mlx);
}

static inline void	handle_player_0(mlx_key_data_t keydata, int id)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		turn (-TURN_SPEED_ARROWS_DEG, id);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		turn (TURN_SPEED_ARROWS_DEG, id);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		setup_player(0);
		setup_player(1);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	int	id;

	id = *((int *) param);
	if (id == 0)
		handle_player_0(keydata, id);
	handle_player(keydata, id);
}
