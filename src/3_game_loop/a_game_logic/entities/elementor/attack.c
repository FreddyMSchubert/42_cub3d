/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:59:57 by freddy            #+#    #+#             */
/*   Updated: 2024/07/05 20:52:31 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define ELEMENTOR_ATTACK_NONE 0
#define ELEMENTOR_ATTACK_NORMAL 1
#define ELEMENTOR_ATTACK_SPIN 2
#define ELEMENTOR_ATTACK_SUMMON 3

static inline void	normal_attack(t_entity *self, t_elementor *elementor)
{
	t_transform	trans;
	int			num;

	trans.rot.x = player()->transform.pos.x - self->transform.pos.x;
	trans.rot.y = player()->transform.pos.y - self->transform.pos.y;
	self->transform.rot = scale_vector(self->transform.rot, 1);
	trans.pos = self->transform.pos;
	self->transform.rot = deg_to_dir_vec(\
		dir_vec_to_deg(self->transform.rot) + (random_val() * \
		LMNTOR_SHOOTING_INACCURACY_DEG - (LMNTOR_SHOOTING_INACCURACY_DEG / 2)));
	if (elementor->stage == 0)
		shooooot(trans, elementor->element1);
	else if (elementor->stage == 1)
	{
		num = random_int(0, 1);
		if (num == 0)
			shooooot(trans, elementor->element1);
		else
			shooooot(trans, elementor->element2);
	}
	else
	{
		num = random_int(0, 2);
		if (num == 0)
			shooooot(trans, elementor->element1);
		else if (num == 1)
			shooooot(trans, elementor->element2);
		else if (num == 2)
			shooooot(trans, elementor->element3);
	}
}

void	elementor_attack(t_entity *self, t_elementor *elementor)
{
	if (elementor->death_animation >= 0)
		return ;
	if (random_val() > LMNTOR_ATTACK_CHANCE)
		return ;
	if (random_val() < LMNTOR_ATTACK_SPIN_CHANCE)
		printf("unimplemented");
	else if (random_val() < LMNTOR_ATTACK_SUMMON_CHANCE)
		printf("unimplemented");
	else
		normal_attack(self, elementor);
}
