/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:57:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 00:21:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_blight(t_entity *self)
{
	t_vec2	new_pos;

	self->transform.rot = scale_vector(self->transform.rot, 1);

	if (random_val() < 0.3)
	{
		// change direction
		self->transform.rot.x = (random_val() * 2) - 1;
		self->transform.rot.y = (random_val() * 2) - 1;
	}

	// move
	new_pos.x = self->transform.pos.x + self->transform.rot.x * BLIGHT_SPEED;
	new_pos.y = self->transform.pos.y + self->transform.rot.y * BLIGHT_SPEED;

	if (is_position_valid(new_pos.x, new_pos.y))
	{
		self->transform.pos.x = new_pos.x;
		self->transform.pos.y = new_pos.y;
	}
}
