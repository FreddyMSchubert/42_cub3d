/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blight_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:05:50 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 17:20:08 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline mlx_texture_t	*get_texture_dying(t_entity *self, t_blight *blight)
{
	t_animation	animation;

	animation.frame1 = NULL;
	if (blight->element == TYPE_FIRE)
		animation = game()->textures.fire_blight_death;
	else if (blight->element == TYPE_AIR)
		animation = game()->textures.air_blight_death;
	else if (blight->element == TYPE_WATER)
		animation = game()->textures.water_blight_death;
	else if (blight->element == TYPE_EARTH)
		animation = game()->textures.earth_blight_death;
	if (!animation.frame1)
		cub_exit("Error: Blight death animation not found!", -1);
	if (self->frames_since_state_change < BLIGHT_DEATH_ANIMATION_FRAMES / 3)
		return (animation.frame1);
	else if (self->frames_since_state_change < 2 * \
						BLIGHT_DEATH_ANIMATION_FRAMES / 3)
		return (animation.frame2);
	else
		return (animation.frame3);
}

static inline mlx_texture_t	*get_texture_attak(t_entity *self, t_blight *blight)
{
	t_animation	animation;

	animation.frame1 = NULL;
	if (blight->element == TYPE_FIRE)
		animation = game()->textures.fire_blight_attack;
	else if (blight->element == TYPE_AIR)
		animation = game()->textures.air_blight_attack;
	else if (blight->element == TYPE_WATER)
		animation = game()->textures.water_blight_attack;
	else if (blight->element == TYPE_EARTH)
		animation = game()->textures.earth_blight_attack;
	if (!animation.frame1)
		cub_exit("Error: Blight attack animation not found!", -1);
	if (self->frames_since_state_change < BLIGHT_ATTACK_ANIMATION_FRAMES / 3)
		return (animation.frame1);
	else if (self->frames_since_state_change < 2 * \
				BLIGHT_ATTACK_ANIMATION_FRAMES / 3)
		return (animation.frame2);
	else
		return (animation.frame3);
}

mlx_texture_t	*get_texture_blight(t_entity *self)
{
	t_blight	*blight;

	blight = (t_blight *)self->data;
	if (blight->state == BLIGHT_STATE_DYING)
		return (get_texture_dying(self, blight));
	else if (blight->state == BLIGHT_STATE_ATTACKING)
		return (get_texture_attak(self, blight));
	else
	{
		if (blight->element == TYPE_FIRE)
			return (game()->textures.fire_blight_idle);
		else if (blight->element == TYPE_AIR)
			return (game()->textures.air_blight_idle);
		else if (blight->element == TYPE_WATER)
			return (game()->textures.water_blight_idle);
		else if (blight->element == TYPE_EARTH)
			return (game()->textures.earth_blight_idle);
		return (game()->textures.fire_blight_idle);
	}
}
