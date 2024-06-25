/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:50:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/25 19:16:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static double	get_mvmnt_speed(int id)
{
	double	speed;

	speed = MOVEMENT_SPEED;
	if (mlx_is_key_down(player(id)->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= MOVEMENT_SPRINT_MULTIPLIER;
	return (speed);
}

static t_vec2	get_movement_from_key(int id)
{
	double	speed;
	double	angle;
	t_vec2	mvmnt;

	speed = get_mvmnt_speed(id);
	angle = deg_to_rad(dir_vec_to_deg(player(id)->transform.rot));
	mvmnt = (t_vec2){0, 0};
	if (mlx_is_key_down(player(id)->mlx, MLX_KEY_W))
	{
		mvmnt.x += cos(angle) * speed;
		mvmnt.y += sin(angle) * speed;
	}
	if (mlx_is_key_down(player(id)->mlx, MLX_KEY_A))
	{
		mvmnt.x += sin(angle) * speed;
		mvmnt.y += -cos(angle) * speed;
	}
	if (mlx_is_key_down(player(id)->mlx, MLX_KEY_S))
	{
		mvmnt.x += -cos(angle) * speed;
		mvmnt.y += -sin(angle) * speed;
	}
	if (mlx_is_key_down(player(id)->mlx, MLX_KEY_D))
	{
		mvmnt.x += -sin(angle) * speed;
		mvmnt.y += cos(angle) * speed;
	}
	return (mvmnt);
}

// we can reuse this function once we have projectiles
bool	is_position_valid(float x, float y, int id)
{
	t_list		*ntt_list;
	t_entity	*ntt;
	t_door		*door;
	float		pos_on_space;

	if (*game()->input_data->map[(int)y][(int)x] != FLOOR)
		return(logger(LOGGER_WARNING, "Can't move there because of a wall."), false);
	ntt_list = game()->entities;
	while (ntt_list)
	{
		ntt = (t_entity *)ntt_list->content;
		if (ntt->type == DOOR_E)
		{
			door = (t_door *)ntt->data;
			if (door->state != DOOR_STATE_OPEN)
			{
				if (door->direction == DOOR_DIR_HORIZONTAL)
				{
					pos_on_space = fmod(y, 1.0f);
					if (floor(player(id)->transform.pos.x) == floor(ntt->transform.pos.x) && floor(player(id)->transform.pos.y) == floor(ntt->transform.pos.y) && \
							pos_on_space > CLOSED_DOOR_ALLOWED_WALK_DISTANCE && pos_on_space < 1 - CLOSED_DOOR_ALLOWED_WALK_DISTANCE)
						return(logger(LOGGER_WARNING, "Can't move there because of a horizontal door."), false);
				}
				else
				{
					pos_on_space = fmod(x, 1.0f);
					if (floor(player(id)->transform.pos.y) == floor(ntt->transform.pos.y) && floor(player(id)->transform.pos.x) == floor(ntt->transform.pos.x) && \
							pos_on_space > CLOSED_DOOR_ALLOWED_WALK_DISTANCE && pos_on_space < 1 - CLOSED_DOOR_ALLOWED_WALK_DISTANCE)
						return(logger(LOGGER_WARNING, "Can't move there because of a vertical door."), false);
				}
			}
		}
		ntt_list = ntt_list->next;
	}
	return (true);
}

void	handle_player_move(int id)
{
	t_vec2	mvmnt;
	t_vec2	new_pos;

	if (id != 0)
		return ;
	mvmnt = get_movement_from_key(id);
	new_pos.x = player(id)->transform.pos.x + mvmnt.x * (1 + WALL_COLLISION_MARGIN);
	new_pos.y = player(id)->transform.pos.y + mvmnt.y * (1 + WALL_COLLISION_MARGIN);
	if (is_position_valid(new_pos.x, player(id)->transform.pos.y, id))
		player(id)->transform.pos.x += mvmnt.x;
	if (is_position_valid(player(id)->transform.pos.x, new_pos.y, id))
		player(id)->transform.pos.y += mvmnt.y;
	if (new_pos.x != player(id)->transform.pos.x || \
					new_pos.y != player(id)->transform.pos.y)
	{
		player(id)->dirty = true;
		if (MARK_DIRTY_LOGGING)
			logger(LOGGER_INFO, "Player 1 moved, set dirty to true!\n");
	}
}
