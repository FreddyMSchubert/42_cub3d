/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 23:59:32 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 00:20:43 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define FRAMES_AMOUNT 10
#define TICKS_PER_FRAME 3

void	tick_explosion(t_entity *self)
{
	self->frames_since_state_change++;
	if (self->frames_since_state_change > FRAMES_AMOUNT)
		self->to_be_deleted = true;
}

mlx_texture_t	*get_texture_explosion(t_entity *self)
{
	int		texture_tick;

	texture_tick = self->frames_since_state_change / TICKS_PER_FRAME;
	if (texture_tick == 1)
		return (game()->textures.explosion_1);
	else if (texture_tick == 2)
		return (game()->textures.explosion_2);
	else if (texture_tick == 3)
		return (game()->textures.explosion_3);
	else if (texture_tick == 4)
		return (game()->textures.explosion_4);
	else if (texture_tick == 5)
		return (game()->textures.explosion_5);
	else if (texture_tick == 6)
		return (game()->textures.explosion_6);
	else if (texture_tick == 7)
		return (game()->textures.explosion_7);
	else if (texture_tick == 8)
		return (game()->textures.explosion_8);
	else if (texture_tick == 9)
		return (game()->textures.explosion_9);
	else if (texture_tick == 10)
		return (game()->textures.explosion_10);
	if (texture_tick > 10)
		return (game()->textures.explosion_10);
	if (texture_tick < 1)
		return (game()->textures.explosion_1);
	return (game()->textures.door);
}
