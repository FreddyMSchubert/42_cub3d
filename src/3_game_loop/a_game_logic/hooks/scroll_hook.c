/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:04:41 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 20:10:57 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// used for player 2s movement

void scroll_hook(double xdelta, double ydelta, void *param)
{
	int		id;
	double	angle;
	double	speed;
	t_vec2	new_pos;
	t_vec2	old_pos;

	(void)xdelta;
	if (game()->player_count == 1)
	{
		if (ydelta != 0)
		{
			if (ydelta > 0)
				player(0)->minimap_size += 1;
			else
				player(0)->minimap_size -= 1;
			if (player(0)->minimap_size < 2)
				player(0)->minimap_size = 2;
			if (player(0)->minimap_size > 6)
				player(0)->minimap_size = 6;
		}
	}
	else
	{
		id = *((int *) param);
		if (id != 1 || game()->player_count < 2)
			return ;
		old_pos = player(id)->transform.pos;
		angle = deg_to_rad(dir_vec_to_deg(player(id)->transform.rot));
		speed = MOVEMENT_SPEED * ydelta;
		new_pos = player(id)->transform.pos;
		new_pos.x += cos(angle) * speed;
		new_pos.y += sin(angle) * speed;
		if (is_position_valid(new_pos.x, player(id)->transform.pos.y, id))
			player(id)->transform.pos.x = new_pos.x;
		if (is_position_valid(player(id)->transform.pos.x, new_pos.y, id))
			player(id)->transform.pos.y = new_pos.y;
		if (old_pos.x != player(id)->transform.pos.x ||
				old_pos.y != player(id)->transform.pos.y)
		{
			player(id)->dirty = true;
			if (MARK_DIRTY_LOGGING)
				logger(LOGGER_INFO, "Player 2 moved, set dirty to true!\n");
		}
	}
}
