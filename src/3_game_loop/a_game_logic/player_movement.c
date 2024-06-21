/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:50:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/21 14:31:41 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static double	get_mvmnt_speed(void)
{
	double	speed;

	speed = MOVEMENT_SPEED;
	if (mlx_is_key_down(game()->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= MOVEMENT_SPRINT_MULTIPLIER;
	return (speed);
}

static t_vec2	get_movement_from_key(void)
{
	double	speed;
	double	angle;
	t_vec2	mvmnt;

	speed = get_mvmnt_speed();
	angle = deg_to_rad(dir_vec_to_deg(player()->transform.rot));
	mvmnt = (t_vec2){0, 0};
	if (mlx_is_key_down(game()->mlx, MLX_KEY_W))
	{
		mvmnt.x += cos(angle) * speed;
		mvmnt.y += sin(angle) * speed;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_A))
	{
		mvmnt.x += sin(angle) * speed;
		mvmnt.y += -cos(angle) * speed;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_S))
	{
		mvmnt.x += -cos(angle) * speed;
		mvmnt.y += -sin(angle) * speed;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_D))
	{
		mvmnt.x += -sin(angle) * speed;
		mvmnt.y += cos(angle) * speed;
	}
	return (mvmnt);
}

void	handle_player_move(void)
{
	t_vec2	mvmnt;
	t_vec2	new_pos;
	t_vec2	old_pos;

	old_pos = player()->transform.pos;
	mvmnt = get_movement_from_key();
	new_pos = (t_vec2){floor(player()->transform.pos.x), \
									floor(player()->transform.pos.y + mvmnt.y)};
	if (*game()->input_data->map[(int)new_pos.y][(int)new_pos.x] == FLOOR)
		player()->transform.pos.y += mvmnt.y;
	new_pos = (t_vec2){floor(player()->transform.pos.x + mvmnt.x), \
											floor(player()->transform.pos.y)};
	if (*game()->input_data->map[(int)new_pos.y][(int)new_pos.x] == FLOOR)
		player()->transform.pos.x += mvmnt.x;
	if (old_pos.x != player()->transform.pos.x || \
					old_pos.y != player()->transform.pos.y)
	{
		game()->dirty = true;
		if (MARK_DIRTY_LOGGING)
			printf("player moved, set dirty to true!\n");
	}
}
