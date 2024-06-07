/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/07 10:41:27 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static t_vec2	get_movement_from_key(mlx_key_data_t keydata)
{
	t_vec2	movement;

	movement = (t_vec2){0, 0};
	if (keydata.key == MLX_KEY_W)
	{
		movement.x = player()->transform.rot.x;
		movement.y = player()->transform.rot.y;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		movement.x = -player()->transform.rot.x;
		movement.y = -player()->transform.rot.y;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		movement.x = -player()->transform.rot.y;
		movement.y = player()->transform.rot.x;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		movement.x = player()->transform.rot.y;
		movement.y = -player()->transform.rot.x;
	}
	return (movement);
}

static void	player_move(mlx_key_data_t keydata)
{
	t_vec2		original_pos;
	t_vec2		movement;

	original_pos = player()->transform.pos;
	if (pos_distance((t_vec2){0, 0}, player()->transform.pos) != MOVEMENT_SPEED)
		player()->transform.rot = scale_transform(player()->transform.rot, MOVEMENT_SPEED);
	movement = get_movement_from_key(keydata);
	player()->transform.pos.x += movement.x;
	player()->transform.pos.y += movement.y;
	if (*game()->input_data->map \
			[(int)player()->transform.pos.y]\
			[(int)player()->transform.pos.x] != FLOOR)
	{
		player()->transform.pos.x = original_pos.x;
		player()->transform.pos.y = original_pos.y;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game()->mlx);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
		player_move(keydata);
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		turn (-TURN_SPEED_ARROWS_DEG);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		turn (TURN_SPEED_ARROWS_DEG);
	(void) param;
}
