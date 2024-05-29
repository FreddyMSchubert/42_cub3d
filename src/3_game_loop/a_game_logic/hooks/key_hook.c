/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/05/29 20:26:41 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static t_vec2	get_movement_from_key(mlx_key_data_t keydata)
{
	t_vec2	movement;

	movement = (t_vec2){0, 0};
	if (keydata.key == MLX_KEY_W)
	{
		movement.x = get_player()->transform.rot.x;
		movement.y = get_player()->transform.rot.y;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		movement.x = -get_player()->transform.rot.x;
		movement.y = -get_player()->transform.rot.y;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		movement.x = -get_player()->transform.rot.y;
		movement.y = get_player()->transform.rot.x;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		movement.x = get_player()->transform.rot.y;
		movement.y = -get_player()->transform.rot.x;
	}
	return (movement);
}

static void	player_move(mlx_key_data_t keydata)
{
	t_vec2		original_pos;
	t_vec2		movement;

	original_pos = get_player()->transform.pos;
	if (pos_distance((t_vec2){0, 0}, get_player()->transform.pos) != MOVEMENT_SPEED)
		get_player()->transform.rot = scale_transform(get_player()->transform.rot, MOVEMENT_SPEED);
	movement = get_movement_from_key(keydata);
	get_player()->transform.pos.x += movement.x;
	get_player()->transform.pos.y += movement.y;
	if (*get_persistent_data()->input_data->map \
			[(int)get_player()->transform.pos.y]\
			[(int)get_player()->transform.pos.x] != FLOOR)
	{
		get_player()->transform.pos.x = original_pos.x;
		get_player()->transform.pos.y = original_pos.y;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(get_persistent_data()->mlx);
	if (keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
			player_move(keydata);
	}
	(void) param;
}
