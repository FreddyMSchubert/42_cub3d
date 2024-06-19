/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/19 16:04:03 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// static t_vec2	get_movement_from_key(mlx_key_data_t keydata, double angle)
// {
// 	t_vec2	movement;

// 	movement = (t_vec2){0, 0};
// 	if (keydata.key == MLX_KEY_W)
// 	{
// 		movement.x = cos(angle) * MOVEMENT_SPEED;
// 		movement.y = sin(angle) * MOVEMENT_SPEED;
// 	}
// 	else if (keydata.key == MLX_KEY_A)
// 	{
// 		movement.x = sin(angle) * MOVEMENT_SPEED;
// 		movement.y = -cos(angle) * MOVEMENT_SPEED;
// 	}
// 	else if (keydata.key == MLX_KEY_S)
// 	{
// 		movement.x = -cos(angle) * MOVEMENT_SPEED;
// 		movement.y = -sin(angle) * MOVEMENT_SPEED;
// 	}
// 	else if (keydata.key == MLX_KEY_D)
// 	{
// 		movement.x = -sin(angle) * MOVEMENT_SPEED;
// 		movement.y = cos(angle) * MOVEMENT_SPEED;
// 	}
// 	return (movement);
// }

// static void	player_move(mlx_key_data_t keydata)
// {
// 	t_vec2		original_pos;
// 	t_vec2		movement;

// 	original_pos = player()->transform.pos;
// 	if (pos_distance((t_vec2){0, 0}, player()->transform.rot) != MOVEMENT_SPEED)
// 		player()->transform.rot = scale_vector(player()->transform.rot, MOVEMENT_SPEED);
// 	movement = get_movement_from_key(keydata, deg_to_rad(dir_vec_to_deg(player()->transform.rot)));
// 	printf("movement: %f, %f, current rot: %f, %f\n", movement.x, movement.y, player()->transform.rot.x, player()->transform.rot.y);
// 	player()->transform.pos.x += movement.x;
// 	player()->transform.pos.y += movement.y;
// 	player()->transform.pos.x += movement.x;
// 	if (*game()->input_data->map[(int)player()->transform.pos.y][(int)player()->transform.pos.x] != FLOOR) {
// 		player()->transform.pos.x = original_pos.x;  // Reset X if colliding
// 	}
// 	player()->transform.pos.y += movement.y;
// 	if (*game()->input_data->map[(int)player()->transform.pos.y][(int)player()->transform.pos.x] != FLOOR) {
// 		player()->transform.pos.y = original_pos.y;  // Reset Y if colliding
// 	}
// }

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game()->mlx);
	// else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
	// 	player_move(keydata);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		turn (-TURN_SPEED_ARROWS_DEG);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		turn (TURN_SPEED_ARROWS_DEG);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		setup_player();
	(void) param;
}
