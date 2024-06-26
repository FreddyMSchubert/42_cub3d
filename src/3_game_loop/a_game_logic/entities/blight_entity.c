/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:57:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 22:17:16 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	tick_blight(t_entity *self)
{
	if (random_val() < 0.1)
	{
		// change direction
		self->transform.rot.x = random_val() * 2 - 1;
		self->transform.rot.y = random_val() * 2 - 1;
	}

	// move
	self->transform.pos.x += self->transform.rot.x * BLIGHT_SPEED;
	self->transform.pos.y += self->transform.rot.y * BLIGHT_SPEED;
}
